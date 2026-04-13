#pragma once

#include "Object/Component.hpp"
#include "Object/Character/Mario.hpp"

namespace MyAPP::Form::Object {

/**
 * @brief Component to handle Mario's state-related sub-behaviors like invincibility and standing checks.
 */
class MarioStateComponent : public Component {
public:
    void Update(void* data) override {
        auto* mario = static_cast<Mario*>(m_Owner);
        if (!mario) return;

        UpdateInvincible(mario);
        UpdateStandCheck(mario);
    }

private:
    void UpdateInvincible(Mario* mario) {
        if (mario->invincibleCount > 0) {
            mario->invincibleCount--;
            switch (mario->mario_type) {
            case Mario::Mario_type::InvincibleMario:
            case Mario::Mario_type::InvincibleSuperMario:
            case Mario::Mario_type::InvincibleFieryMario:
                mario->index++;
                mario->changeImg();
                break;
            default:
                break;
            }
        }
        else {
            mario->collisionable = true;
            switch (mario->mario_type) {
            case Mario::Mario_type::InvincibleMario:
                mario->changeType(Mario::Mario_type::Mario);
                mario->index++;
                mario->changeImg();
                break;
            case Mario::Mario_type::InvincibleSuperMario:
                mario->changeType(Mario::Mario_type::SuperMario);
                mario->index++;
                mario->changeImg();
                break;
            case Mario::Mario_type::InvincibleFieryMario:
                mario->changeType(Mario::Mario_type::FieryMario);
                mario->index++;
                mario->changeImg();
                break;
            default:
                break;
            }
        }
    }

    void UpdateStandCheck(Mario* mario) {
        if (mario->STANDCount > 0) {
            mario->STANDCount--;
        }
        else if (mario->state == Mario::State::MOVE) {
            mario->state = Mario::State::STAND;
            mario->changeImg();
        }
    }
};

} // namespace MyAPP::Form::Object
