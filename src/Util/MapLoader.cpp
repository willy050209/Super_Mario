#include "Util/MapLoader.hpp"
#include "Object/MakeObject.hpp"
#include <fstream>
#include <iostream>

namespace MyAPP::Util {

void MapLoader::LoadMap(const std::string& jsonPath, const std::string& formName, MyAPP::Form::FormManager& FM) {
    std::ifstream file(jsonPath);
    if (!file.is_open()) {
        std::cerr << "Failed to open map file: " << jsonPath << std::endl;
        return;
    }

    json mapData;
    file >> mapData;

    // Load Bricks (and other static images)
    if (mapData.contains("bricks")) {
        auto bricks = MyAPP::Form::Object::MakeObject::make_Bricks();
        for (const auto& brickData : mapData["bricks"]) {
            MyAPP::Form::Object::MakeObject::Fileinfo info;
            info.Type = brickData["type"];
            info.XY = { (float)brickData["x"], (float)brickData["y"] };
            info.Visibility = brickData.value("visible", true) ? 1 : 0;
            info.Collisionable = brickData.value("collisionable", true) ? 1 : 0;
            info.data = brickData.value("data", "");
            
            info.ChangeXY(); // Convert grid to world coordinates
            
            auto color = static_cast<MyAPP::Form::Object::BrickColor>(brickData.value("color", 0));
            auto ptr = MyAPP::Form::Object::MakeObject::make_BrickPtr(info, color);
            if (ptr) {
                bricks->push_back(ptr);
            }
        }
        // Instead of adding the vector, we add each object to maintain FM state
        for (auto& brick : *bricks) {
            FM.addObject(formName, brick);
        }
    }

    // Load Enemies
    if (mapData.contains("enemies")) {
        for (const auto& enemyData : mapData["enemies"]) {
            MyAPP::Form::Object::MakeObject::Fileinfo info;
            info.Type = enemyData["type"];
            info.XY = { (float)enemyData["x"], (float)enemyData["y"] };
            info.Visibility = 1;
            info.Collisionable = 1;
            info.data = enemyData.value("data", "");
            
            info.ChangeXY(); // Convert grid to world coordinates
            
            auto enemy = MyAPP::Form::Object::MakeObject::make_EnemysPtr(info);
            if (enemy) {
                FM.addObject(formName, enemy);
            }
        }
    }

    std::cout << "Successfully loaded map: " << jsonPath << " into form: " << formName << std::endl;
}

} // namespace MyAPP::Util
