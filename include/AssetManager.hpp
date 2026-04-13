#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include "Util/Image.hpp"
#include "Util/BGM.hpp"
#include "Util/SFX.hpp"

namespace MyAPP {

/**
 * @brief Centralized manager for game assets to implement caching and resource sharing.
 */
class AssetManager {
public:
    /**
     * @brief Get the singleton instance of AssetManager.
     */
    static AssetManager& GetInstance() {
        static AssetManager instance;
        return instance;
    }

    AssetManager(const AssetManager&) = delete;
    AssetManager& operator=(const AssetManager&) = delete;

    /**
     * @brief Loads or retrieves a cached image.
     * @param path The filesystem path to the image.
     * @return std::shared_ptr<Util::Image>
     */
    std::shared_ptr<Util::Image> GetImage(const std::string& path) {
        auto it = m_Images.find(path);
        if (it == m_Images.end()) {
            it = m_Images.emplace(path, std::make_shared<Util::Image>(path)).first;
        }
        return it->second;
    }

    /**
     * @brief Loads or retrieves a cached BGM.
     * @param path The filesystem path to the BGM file.
     * @return std::shared_ptr<Util::BGM>
     */
    std::shared_ptr<Util::BGM> GetBGM(const std::string& path) {
        auto it = m_BGMs.find(path);
        if (it == m_BGMs.end()) {
            it = m_BGMs.emplace(path, std::make_shared<Util::BGM>(path)).first;
        }
        return it->second;
    }

    /**
     * @brief Loads or retrieves a cached SFX.
     * @param path The filesystem path to the SFX file.
     * @return std::shared_ptr<Util::SFX>
     */
    std::shared_ptr<Util::SFX> GetSFX(const std::string& path) {
        auto it = m_SFXs.find(path);
        if (it == m_SFXs.end()) {
            it = m_SFXs.emplace(path, std::make_shared<Util::SFX>(path)).first;
        }
        return it->second;
    }

    /**
     * @brief Clears all cached assets.
     */
    void Clear() {
        m_Images.clear();
        m_BGMs.clear();
        m_SFXs.clear();
    }

private:
    AssetManager() = default;

    std::unordered_map<std::string, std::shared_ptr<Util::Image>> m_Images;
    std::unordered_map<std::string, std::shared_ptr<Util::BGM>> m_BGMs;
    std::unordered_map<std::string, std::shared_ptr<Util::SFX>> m_SFXs;
};

} // namespace MyAPP
