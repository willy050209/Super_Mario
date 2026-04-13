#include "Object/PhysicsComponent.hpp"
#include "Object/Object.hpp"
#include "Object/Brick/Brick.hpp"
#include "config.hpp"
#include <algorithm>

namespace MyAPP::Form::Object {

void PhysicsComponent::Update(void* data) {
    if (!m_Owner) return;

    // Apply gravity
    if (m_UseGravity && !m_IsOnGround) {
        m_Velocity.y += GRAVITY;
        if (m_Velocity.y < TERMINAL_VELOCITY) {
            m_Velocity.y = TERMINAL_VELOCITY;
        }
    }

    // Move
    m_Owner->incPositionX(m_Velocity.x);
    m_Owner->incPositionY(m_Velocity.y);

    // Ground check will be updated by ResolveCollisions
    m_IsOnGround = false; 
}

void PhysicsComponent::ResolveCollisions(const std::vector<std::shared_ptr<Brick>>& bricks) {
    if (!m_Owner) return;

    glm::vec2 pos = m_Owner->GetPosition();
    glm::vec2 size = m_Owner->GetSize();

    for (const auto& brick : bricks) {
        if (!brick || !brick->collisionable) continue;

        if (m_Owner->inRange(brick->GetPosition(), brick->GetSize())) {
            glm::vec2 bPos = brick->GetPosition();
            glm::vec2 bSize = brick->GetSize();

            // Calculate overlap on both axes
            float overlapX = (size.x + bSize.x) / 2.0f - std::abs(pos.x - bPos.x);
            float overlapY = (size.y + bSize.y) / 2.0f - std::abs(pos.y - bPos.y);

            if (overlapX > 0 && overlapY > 0) {
                // Resolve on the axis with smaller overlap to minimize jitter
                if (overlapX < overlapY) {
                    if (pos.x < bPos.x) {
                        m_Owner->incPositionX(-overlapX);
                    } else {
                        m_Owner->incPositionX(overlapX);
                    }
                    m_Velocity.x = 0;
                } else {
                    if (pos.y < bPos.y) {
                        // Hit ceiling
                        m_Owner->incPositionY(-overlapY);
                        m_Velocity.y = 0;
                    } else {
                        // Landed on ground
                        m_Owner->incPositionY(overlapY);
                        m_Velocity.y = 0;
                        m_IsOnGround = true;
                    }
                }
                // Update pos after adjustment for next brick check
                pos = m_Owner->GetPosition();
            }
        }
    }
}

} // namespace MyAPP::Form::Object
