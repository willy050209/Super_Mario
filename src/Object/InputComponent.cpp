#include "Object/InputComponent.hpp"
#include "Util/Input.hpp"
#include "config.hpp"

namespace MyAPP::Form::Object {

void InputComponent::Update(void* data) {
    // Decay existing buffer
    float deltaTime = 1.0f / (float)FPS_CAP;
    
    size_t size = m_Buffer.size();
    for (size_t i = 0; i < size; ++i) {
        auto input = m_Buffer.front();
        m_Buffer.pop();
        input.timeLeft -= deltaTime;
        if (input.timeLeft > 0) {
            m_Buffer.push(input);
        }
    }

    // Capture new down presses
    // For now, we only buffer Jump (UP)
    if (Util::Input::IsKeyDown(Util::Keycode::UP)) {
        m_Buffer.push({Util::Keycode::UP, BUFFER_DURATION});
    }
}

bool InputComponent::IsKeyPressed(Util::Keycode key) const {
    return Util::Input::IsKeyPressed(key);
}

bool InputComponent::IsKeyDown(Util::Keycode key) const {
    return Util::Input::IsKeyDown(key);
}

bool InputComponent::WasKeyPressedBuffered(Util::Keycode key) {
    // Note: This is a simple implementation. In a real ECS we might use a temporary queue.
    std::queue<BufferedInput> temp;
    bool found = false;
    while (!m_Buffer.empty()) {
        if (m_Buffer.front().key == key) found = true;
        temp.push(m_Buffer.front());
        m_Buffer.pop();
    }
    m_Buffer = temp;
    return found;
}

void InputComponent::ConsumeBuffer(Util::Keycode key) {
    std::queue<BufferedInput> temp;
    while (!m_Buffer.empty()) {
        if (m_Buffer.front().key != key) {
            temp.push(m_Buffer.front());
        }
        m_Buffer.pop();
    }
    m_Buffer = temp;
}

} // namespace MyAPP::Form::Object
