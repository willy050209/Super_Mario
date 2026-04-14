#include "Object/AudioComponent.hpp"
#include "AssetManager.hpp"

namespace MyAPP::Form::Object {

void AudioComponent::AddSound(const std::string& label, const std::string& path) {
    m_Sounds[label] = AssetManager::GetInstance().GetSFX(path);
}

void AudioComponent::Play(const std::string& label, int loops, int volume) {
    auto it = m_Sounds.find(label);
    if (it != m_Sounds.end() && it->second) {
        if (volume >= 0) {
            it->second->SetVolume(volume);
        }
        it->second->Play(loops);
    }
}

} // namespace MyAPP::Form::Object
