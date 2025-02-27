#ifndef CONFIG_H
#define CONFIG_H

#include "pch.hpp" // IWYU pragma: export

#include "Util/Logger.hpp"

constexpr const char *TITLE = "My Super Mario";

extern int WINDOW_POS_X; // = SDL_WINDOWPOS_UNDEFINED;
extern int WINDOW_POS_Y; // = SDL_WINDOWPOS_UNDEFINED;

extern int WINDOW_WIDTH; // = 1280;
extern int WINDOW_HEIGHT; // = 720;

constexpr Util::Logger::Level DEFAULT_LOG_LEVEL = Util::Logger::Level::DEBUG;

/**
 * @brief FPS limit
 *
 * Set value to 0 to turn off FPS cap
 */
extern unsigned int FPS_CAP;// = 60;

#endif
