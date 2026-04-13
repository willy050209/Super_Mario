#include "Object/Character/Turtle.hpp"
#include "config.hpp"
#include "ImageObject.hpp"
#include "GameManager.hpp"
#include "AssetManager.hpp"
#include "Constants.hpp"

#include <memory>
#include <execution>
#include <algorithm>

namespace MyAPP::Form::Object {

Turtle::Turtle(const std::string& name, int zindex)
    : Character(name, Frames[0], zindex) {
    MyType = ObjectType::Turtle;
    left = 1;
    
    m_Physics = &AddComponent<PhysicsComponent>(true);
    m_Physics->SetVelocity({-2.0f, 0});
    
    m_Animation = &AddComponent<AnimationComponent>(6.0f);
    m_Animation->AddAnimation("walk_L", { Frames[0], Frames[1] });
    m_Animation->AddAnimation("walk_R", { imgs_r[0], imgs_r[1] });
    m_Animation->AddAnimation("walk_dark_L", { FramesDark[0], FramesDark[1] });
    m_Animation->AddAnimation("walk_dark_R", { darkimgs_r[0], darkimgs_r[1] });
    m_Animation->AddAnimation("walk_red_L", { FramesRed[0], FramesRed[1] });
    m_Animation->AddAnimation("walk_red_R", { Redimgs_r[0], Redimgs_r[1] });
    m_Animation->Play("walk_L");
}

void Turtle::behavior(void* data) {
    auto GM = static_cast<GameManager*>(data);
    if (!GM->pause) {
        if (diedFlag && !moveFlag) return;

        // Base component updates
        Object::behavior(data);

        // Animation logic
        if (!diedFlag) {
            std::string themePrefix = dark ? "walk_dark_" : (turtlecolor == TurtleColor::Red ? "walk_red_" : "walk_");
            m_Animation->Play(themePrefix + (left ? "L" : "R"));
        }

        // Collision with bricks
        auto bricks = std::static_pointer_cast<BrickPtrVec>(userdata);
        if (bricks) {
            m_Physics->ResolveCollisions(*bricks);
            if (m_Physics->GetVelocity().x == 0 && !diedFlag) {
                left = !left;
                m_Physics->SetVelocity({ (left ? -2.0f : 2.0f), m_Physics->GetVelocity().y });
            }
        }

        CheckCollision(data);
    }
}

void Turtle::died() noexcept {
    diedFlag = true;
    moveFlag = false;
    m_Physics->SetVelocity({0, 0});
    
    std::string shellImg = TortoiseShell;
    if (dark) shellImg = DarkTortoiseShell;
    else if (turtlecolor == TurtleColor::Red) shellImg = RedTortoiseShell;
    
    setImage(shellImg);
}

void Turtle::Reset() noexcept {
    Character::Reset();
    diedFlag = false;
    moveFlag = true;
    m_Physics->SetVelocity({-2.0f, 0});
}

void Turtle::CheckCollision(void* data) {
    auto GM = static_cast<MyAPP::GameManager*>(data);
    auto& FM = GM->GetFormManager();
    auto mario = FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario");
    if (!mario || GM->opMode || mario->GetState() == Mario::State::DIED) return;

    if (collisionable && mario->collisionable && inRange(mario->GetPosition(), mario->GetSize())) {
        if (diedFlag) {
            // Kick the shell
            moveFlag = true;
            left = (mario->GetPosition().x < GetPosition().x) ? 0 : 1;
            m_Physics->SetVelocity({ (left ? -6.0f : 6.0f), 0 });
        }
        else if (mario->isInvincible() || (mario->GetState() == Mario::State::DOWN && mario->getBottom() > getBottom())) {
            died();
            GM->addPoint(200);
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
