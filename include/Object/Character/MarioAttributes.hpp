#pragma once
#include "Object/Character/MarioEnums.hpp"
#include <string>
#include <vector>
#include <unordered_map>

namespace MyAPP::Form::Object {

class Mario; // Forward declaration
/**
 * @brief Configuration structure for different Mario types (Small, Super, Fire).
 */
struct MarioTypeConfig {
    std::string name;
    std::unordered_map<MarioState, std::vector<std::vector<std::string>>> animations; // [state][facing_left][frames]
    float jumpForce;
    float moveSpeed;
    bool canBreakBricks;
};

/**
 * @brief Provides access to Mario's configuration based on his current type.
 */
class MarioConfigProvider {
public:
    static const MarioTypeConfig& GetConfig(MarioType type);

private:
    static void Initialize();
    static inline std::unordered_map<MarioType, MarioTypeConfig> s_Configs;
    static inline bool s_Initialized = false;
};

} // namespace MyAPP::Form::Object
