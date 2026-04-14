#pragma once

namespace MyAPP::Form::Object {

class Object;

/**
 * @brief Base class for all components in the ECS-like architecture.
 */
class Component {
public:
    virtual ~Component() = default;

    /**
     * @brief Update logic for the component.
     * @param data Pointer to GameManager or other context data.
     */
    virtual void Update(void* data) {}

    /**
     * @brief Set the owner object of this component.
     */
    void SetOwner(Object* owner) { m_Owner = owner; }

    /**
     * @brief Get the owner object of this component.
     */
    Object* GetOwner() const { return m_Owner; }

protected:
    Object* m_Owner = nullptr;
};

} // namespace MyAPP::Form::Object
