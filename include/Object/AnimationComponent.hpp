#pragma once
#include "Component.hpp"
#include <vector>
#include <string>
#include <memory>

namespace MyAPP::Form::Object {

/**
 * @brief Handles frame-based animations using AssetManager.
 */
class AnimationComponent : public Component {
public:
    AnimationComponent(float framesPerSecond = 10.0f) 
        : m_FPS(framesPerSecond) {}

    virtual void Update(void* data) override;

    void AddAnimation(const std::string& name, const std::vector<std::string>& frames);
    void Play(const std::string& name, bool loop = true);
    void SetFPS(float fps) { m_FPS = fps; }

    const std::string& GetCurrentAnimation() const { return m_CurrentAnim; }

private:
    std::unordered_map<std::string, std::vector<std::string>> m_Animations;
    std::string m_CurrentAnim;
    size_t m_CurrentFrame = 0;
    float m_FPS = 10.0f;
    float m_Timer = 0.0f;
    bool m_Loop = true;
};

} // namespace MyAPP::Form::Object
