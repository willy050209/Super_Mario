#include "Object/Character/Goomba.hpp"
#include "config.hpp"
#include "ImageObject.hpp"
#include "GameManager.hpp"
#include "AssetManager.hpp"
#include "Constants.hpp"

#include <memory>
#include <execution>
#include <algorithm>

namespace MyAPP::Form::Object {

Goomba::Goomba(const std::string& name, int zindex)
    : Character(name, Frames[0], zindex) {
    MyType = ObjectType::Goomba;
    left = 1;
    
    m_Physics = &AddComponent<PhysicsComponent>(true);
    m_Physics->SetVelocity({-2.0f, 0}); // Constant walking speed
    
    m_Animation = &AddComponent<AnimationComponent>(6.0f);
    m_Animation->AddAnimation("walk", { Frames[0], Frames[1] });
    m_Animation->AddAnimation("walk_dark", { FramesDark[0], FramesDark[1] });
    m_Animation->Play("walk");
}

void Goomba::behavior(void* data) {
    auto GM = static_cast<GameManager*>(data);
    if (!GM->pause) {
        if (isDied) return;

        // Base component updates
        Object::behavior(data);

        // Animation update based on theme
        if (dark) m_Animation->Play("walk_dark");
        else m_Animation->Play("walk");

        // Collision with bricks
        auto bricks = std::static_pointer_cast<BrickPtrVec>(userdata);
        if (bricks) {
            float oldVelX = m_Physics->GetVelocity().x;
            m_Physics->ResolveCollisions(*bricks);
            
            // If horizontal velocity was zeroed out by PhysicsComponent, it means we hit a wall
            // In a real system we'd check if we were pushed, but for now we can check if we hit something.
            // Let's implement a simple bounce logic:
            if (m_Physics->GetVelocity().x == 0 && !isDied) {
                left = !left;
                m_Physics->SetVelocity({ (left ? -2.0f : 2.0f), m_Physics->GetVelocity().y });
            }
        }

        CheckCollision(data);
    }
}

void Goomba::died() noexcept {
    isDied = true;
    collisionable = false;
    m_Visible = false;
}

void MyAPP::Form::Object::Goomba::CheckCollision(void* data) {
    auto GM = static_cast<MyAPP::GameManager*>(data);
    auto& FM = GM->GetFormManager();
    auto mario = FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario");
    if (!mario || GM->opMode || mario->GetState() == Mario::State::DIED) return;

    if (collisionable && mario->collisionable && inRange(mario->GetPosition(), mario->GetSize())) {
        if (mario->isInvincible() || (mario->GetState() == Mario::State::DOWN && mario->getBottom() > getBottom())) {
            died();
            // Point logic... (omitted for brevity but should be kept in real implementation)
            GM->addPoint(100);
            if (mario->GetState() == Mario::State::DOWN) {
                mario->jump(1.0);
            }
        }
        else if (mario->GetState() != Mario::State::UP) {
            mario->died();
            if (mario->isdied()) {
                GM->LostALife();
            }
        }
    }
}

} // namespace MyAPP::Form::Object
