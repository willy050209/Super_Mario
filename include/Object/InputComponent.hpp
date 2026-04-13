#pragma once
#include "Component.hpp"
#include <unordered_map>
#include "Util/Keycode.hpp"
#include <queue>

namespace MyAPP::Form::Object {

/**
 * @brief Handles input with buffering for smoother gameplay (e.g. jump buffering).
 */
class InputComponent : public Component {
public:
    struct BufferedInput {
        Util::Keycode key;
        float timeLeft;
    };

    virtual void Update(void* data) override;

    bool IsKeyPressed(Util::Keycode key) const;
    bool IsKeyDown(Util::Keycode key) const;
    
    /**
     * @brief Checks if a key was pressed within the buffer window.
     */
    bool WasKeyPressedBuffered(Util::Keycode key);

    void ConsumeBuffer(Util::Keycode key);

private:
    std::queue<BufferedInput> m_Buffer;
    static constexpr float BUFFER_DURATION = 0.15f; // 150ms buffer
};

} // namespace MyAPP::Form::Object
