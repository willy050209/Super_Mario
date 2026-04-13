#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "Form/FormManager.hpp"

namespace MyAPP::Util {

/**
 * @brief Handles loading game maps from JSON files and populating the FormManager.
 */
class MapLoader {
public:
    static void LoadMap(const std::string& jsonPath, const std::string& formName, MyAPP::Form::FormManager& FM);

private:
    using json = nlohmann::json;
};

} // namespace MyAPP::Util
