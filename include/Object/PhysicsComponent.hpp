#pragma once
#include "Component.hpp"
#include <glm/vec2.hpp>
#include <vector>
#include <memory>

namespace MyAPP::Form::Object {

class Brick;

/**
 * @brief Handles gravity, velocity, and basic AABB collision resolution.
 */
class PhysicsComponent : public Component {
public:
    PhysicsComponent(bool useGravity = true) : m_UseGravity(useGravity) {}

    virtual void Update(void* data) override;

    void SetVelocity(const glm::vec2& vel) { m_Velocity = vel; }
    const glm::vec2& GetVelocity() const { return m_Velocity; }
    
    void ApplyImpulse(const glm::vec2& impulse) { m_Velocity += impulse; }

    bool IsOnGround() const { return m_IsOnGround; }

    /**
     * @brief Resolves collisions with a set of bricks.
     */
    void ResolveCollisions(const std::vector<std::shared_ptr<Brick>>& bricks);

private:
    glm::vec2 m_Velocity{0.0f, 0.0f};
    bool m_UseGravity = true;
    bool m_IsOnGround = false;
    
    // Constants (could be moved to Constants.hpp later)
    static constexpr float GRAVITY = -0.5f; 
    static constexpr float TERMINAL_VELOCITY = -10.0f;
};

} // namespace MyAPP::Form::Object
