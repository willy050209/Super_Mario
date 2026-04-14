#pragma once
#include <SDL.h>
#include "config.hpp"
#include <string>

namespace MyAPP {

namespace Constants {
    // Window Settings
    inline constexpr int DEFAULT_WINDOW_WIDTH = 640;
    inline constexpr int DEFAULT_WINDOW_HEIGHT = 480;
    inline constexpr unsigned int DEFAULT_FPS_CAP = 60;
    inline constexpr int DEFAULT_WINDOW_POS_X = SDL_WINDOWPOS_UNDEFINED;
    inline constexpr int DEFAULT_WINDOW_POS_Y = SDL_WINDOWPOS_UNDEFINED;

    // baseline for scaling
    inline constexpr double BASELINE_HEIGHT = 480.0;

    // Audio Settings
    inline constexpr int DEFAULT_BGM_VOLUME = 50;

    // File Paths
    inline const std::string PROFILE_FILE = "Form Profile";
    inline const std::string IMAGERESIZER_EXE_PATH = MY_IMAGERESIZER_DIR "/ImageResizer.exe";
    inline const std::string RESOURCE_DIR = MY_RESOURCE_DIR;
    inline const std::string MARIO_RESOURCE_DIR = MY_RESOURCE_DIR "/super mario";
    inline const std::string KAPOO_RESOURCE_DIR = MY_RESOURCE_DIR "/Kapoo";
    inline const std::string OUTPUT_IMG_DIR = "imgs";
    inline const std::string MARIO_OUTPUT_DIR = "imgs/super mario";
    
    inline const std::string ICON_PATH = MY_RESOURCE_DIR "/image/ICON/images.png";

    // Physics Settings
    inline constexpr float GRAVITY = -0.6f;
    inline constexpr float TERMINAL_VELOCITY = -12.0f;
    inline constexpr float JUMP_FORCE = 12.0f;
    inline constexpr float MOVE_SPEED = 4.0f;
    inline constexpr float FRICTION = 0.9f;
    inline constexpr float AIR_RESISTANCE = 0.98f;
}

} // namespace MyAPP
