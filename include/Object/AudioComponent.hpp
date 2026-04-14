#pragma once
#include "Component.hpp"
#include "Util/SFX.hpp"
#include <string>
#include <unordered_map>
#include <memory>

namespace MyAPP::Form::Object {

/**
 * @brief Component for handling sound effects using AssetManager caching.
 */
class AudioComponent : public Component {
public:
    AudioComponent() = default;

    virtual void Update(void* data) override {} // No per-frame logic needed for playback trigger

    /**
     * @brief Adds a sound effect mapping.
     * @param label Name of the sound (e.g., "Jump")
     * @param path File path to the audio resource.
     */
    void AddSound(const std::string& label, const std::string& path);

    /**
     * @brief Plays a sound effect by its label.
     */
    void Play(const std::string& label, int loops = 0, int volume = -1);

private:
    std::unordered_map<std::string, std::shared_ptr<Util::SFX>> m_Sounds;
};

} // namespace MyAPP::Form::Object
