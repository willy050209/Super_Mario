#pragma once
#include "Object/Character/Mario.hpp"
#include <string>
#include <vector>
#include <unordered_map>

namespace MyAPP::Form::Object {

/**
 * @brief Configuration structure for different Mario types (Small, Super, Fire).
 */
struct MarioTypeConfig {
    std::string name;
    std::unordered_map<Mario::State, std::vector<std::vector<std::string>>> animations; // [state][facing_left][frames]
    float jumpForce;
    float moveSpeed;
    bool canBreakBricks;
};

/**
 * @brief Provides access to Mario's configuration based on his current type.
 */
class MarioConfigProvider {
public:
    static const MarioTypeConfig& GetConfig(Mario::Mario_type type);

private:
    static void Initialize();
    static inline std::unordered_map<Mario::Mario_type, MarioTypeConfig> s_Configs;
    static inline bool s_Initialized = false;
};

} // namespace MyAPP::Form::Object
