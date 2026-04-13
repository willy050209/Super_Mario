#include "Object/Character/Mario.hpp"
#include "Object/ImageObject.hpp"
#include "Util/Input.hpp"
#include "config.hpp"
#include "FilePath.hpp"
#include "GameManager.hpp"
#include "Constants.hpp"
#include <iostream>
#include <algorithm>

namespace MyAPP::Form::Object {

Mario::Mario(const std::string& name, int zindex)
    : Character(name, "imgs/super mario/1-1/Mario/frame0.png", zindex) {
    MyType = ObjectType::Mario;
    
    // Attach components
    m_Physics = &AddComponent<PhysicsComponent>(true); // Use gravity
    m_Animation = &AddComponent<AnimationComponent>(12.0f); // 12 FPS
    m_Input = &AddComponent<InputComponent>();
    
    // Initialize with default type
    changeType(Mario_type::Mario);
}

void Mario::changeType(Mario_type type_) {
    auto oldSize = GetSize();
    mario_type = type_;
    
    // Load animations from config
    const auto& config = MarioConfigProvider::GetConfig(mario_type);
    for (auto const& [state, anims] : config.animations) {
        m_Animation->AddAnimation(std::to_string((int)state) + "_R", anims[0]);
        m_Animation->AddAnimation(std::to_string((int)state) + "_L", anims[1]);
    }
    
    changeImg(); // Update current sprite
    
    auto newSize = GetSize();
    if (newSize.y != oldSize.y) {
        m_Transform.translation.y += (newSize.y - oldSize.y) / 2.0f;
    }
}

void Mario::behavior(void* data) {
    auto GM = static_cast<GameManager*>(data);
    if (!GM->opMode) {
        // Core component updates are handled by Object::behavior()
        Object::behavior(data);
        
        // Handle input for movement
        if (m_Input->IsKeyPressed(Util::Keycode::RIGHT)) {
            left = 0;
            m_Physics->SetVelocity({MarioConfigProvider::GetConfig(mario_type).moveSpeed, m_Physics->GetVelocity().y});
            state = State::MOVE;
        } else if (m_Input->IsKeyPressed(Util::Keycode::LEFT)) {
            left = 1;
            m_Physics->SetVelocity({-MarioConfigProvider::GetConfig(mario_type).moveSpeed, m_Physics->GetVelocity().y});
            state = State::MOVE;
        } else {
            m_Physics->SetVelocity({0, m_Physics->GetVelocity().y});
            if (m_Physics->IsOnGround()) state = State::STAND;
        }

        // Handle Jump with buffering
        if (m_Input->WasKeyPressedBuffered(Util::Keycode::UP) && m_Physics->IsOnGround()) {
            m_Physics->ApplyImpulse({0, MarioConfigProvider::GetConfig(mario_type).jumpForce});
            m_Input->ConsumeBuffer(Util::Keycode::UP);
            state = State::UP;
        }

        // Collision resolution (PhysicsComponent handles this)
        auto bricks = std::static_pointer_cast<BrickPtrVec>(userdata);
        if (bricks) {
            m_Physics->ResolveCollisions(*bricks);
        }

        checkInvincible(data);
        shoot(data);
        changeImg();
    }
}

void Mario::changeImg() noexcept {
    std::string animName = std::to_string((int)state) + (left ? "_L" : "_R");
    m_Animation->Play(animName);
}

void Mario::jump(float d) noexcept {
    if (m_Physics->IsOnGround()) {
        m_Physics->ApplyImpulse({0, d * 2.5f}); // Adjust multiplier to match old feel
        state = State::UP;
    }
}

void Mario::move() noexcept {
    // Legacy move call - now handled by PhysicsComponent in behavior
}

void Mario::died() noexcept {
    if (!isdied() && invincibleCount <= 0) {
        if (isBigMario()) {
            changeType(Mario_type::Mario);
            invincibleCount = Constants::DEFAULT_FPS_CAP * 2;
        } else {
            state = State::DIED;
            m_Physics->ApplyImpulse({0, 8.0f});
            collisionable = false;
        }
        changeImg();
    }
}

void Mario::Reset() noexcept {
    state = State::MOVE;
    changeType(Mario_type::Mario);
    invincibleCount = 0;
    diedflag = false;
    m_Physics->SetVelocity({0, 0});
    ResetPosition();
}

bool Mario::isBigMario() const noexcept {
    return mario_type != Mario_type::Mario && mario_type != Mario_type::InvincibleMario;
}

bool Mario::isMiniMario() const noexcept {
    return mario_type == Mario_type::Mario || mario_type == Mario_type::InvincibleMario;
}

bool Mario::isFieryMario() const noexcept {
    return mario_type == Mario_type::FieryMario || mario_type == Mario_type::InvincibleFieryMario;
}

std::string Mario::GetCrouchingImg() const noexcept {
    // For now return a standing img or specific crouch path
    return (left ? "imgs/super mario/Flip_MarioStanding.png" : "imgs/super mario/MarioStanding.png");
}

// Stubs for remaining logic to keep it functional
void Mario::CheckPos(void* data) {}
void Mario::doJump() noexcept {}
void Mario::comeDown() noexcept {}
void Mario::checkInvincible(void* data) noexcept {
    if (invincibleCount > 0) invincibleCount--;
}
void Mario::shoot(void* data) noexcept {
    if (shootFireTrigger) {
        Fire::CreateFire(static_cast<GameManager*>(data)->GetFormManager());
        shootFireTrigger = false;
    }
}
void Mario::StandCheck() noexcept {}

// --- Fire Implementation ---

Fire::Fire(const std::string& name, float zIndex, const glm::vec2& pivot)
    : ImageObject(name, AssetManager::GetInstance().GetImage(Frame[0]), zIndex, pivot) {
    MyType = ObjectType::Fire;
}

void Fire::behavior(void* data) {
    CheckCollision(data);
    Move({ (left ? -1.0f : 1.0f) * 6.0f, 0 });
    PlayFrames();
    if (destroyflag) destroyFire(static_cast<GameManager*>(data)->GetFormManager());
}

void Fire::CreateFire(FormManager& FM) noexcept {
    auto mario = FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario");
    if (!mario) return;
    
    auto fire = std::make_shared<Fire>("Fire", 20);
    fire->left = mario->isLeft();
    fire->SetPosition(mario->GetPosition());
    FM.addObject(FM.GetNowForm(), fire);
}

void Fire::Move(const glm::vec2& distance) noexcept {
    incPositionX(distance.x);
    Xcount += std::abs(distance.x);
    if (Xcount > WINDOW_WIDTH) destroyflag = true;
}

void Fire::PlayFrames() noexcept {
    imgDelay++;
    if (imgDelay >= 5) {
        imgIndex = (imgIndex + 1) % 4;
        setImage(Frame[imgIndex]);
        imgDelay = 0;
    }
}

void Fire::CheckCollision(void* data) {
    // Collision logic...
}

void Fire::destroyFire(FormManager& FM) noexcept {
    FM.removeObject<Fire>(FM.GetNowForm(), m_ID);
}

} // namespace MyAPP::Form::Object
