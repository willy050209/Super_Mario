#include "Object/AnimationComponent.hpp"
#include "Object/Object.hpp"
#include "config.hpp"

namespace MyAPP::Form::Object {

void AnimationComponent::Update(void* data) {
    if (m_CurrentAnim.empty() || !m_Owner) return;

    const auto& frames = m_Animations[m_CurrentAnim];
    if (frames.empty()) return;

    m_Timer += 1.0f / (float)FPS_CAP;
    if (m_Timer >= 1.0f / m_FPS) {
        m_Timer = 0;
        m_CurrentFrame++;
        if (m_CurrentFrame >= frames.size()) {
            if (m_Loop) {
                m_CurrentFrame = 0;
            } else {
                m_CurrentFrame = frames.size() - 1;
            }
        }
        m_Owner->setImage(frames[m_CurrentFrame]);
    }
}

void AnimationComponent::AddAnimation(const std::string& name, const std::vector<std::string>& frames) {
    m_Animations[name] = frames;
}

void AnimationComponent::Play(const std::string& name, bool loop) {
    if (m_CurrentAnim == name) return;
    if (m_Animations.count(name)) {
        m_CurrentAnim = name;
        m_CurrentFrame = 0;
        m_Timer = 0;
        m_Loop = loop;
        m_Owner->setImage(m_Animations[m_CurrentAnim][0]);
    }
}

} // namespace MyAPP::Form::Object
