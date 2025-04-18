#pragma once
#ifndef CONFIG_H
#define CONFIG_H

#include "pch.hpp" // IWYU pragma: export

#include "Util/Logger.hpp"


constexpr const char *TITLE = "My Super Mario";

extern int WINDOW_POS_X; // = SDL_WINDOWPOS_UNDEFINED;
extern int WINDOW_POS_Y; // = SDL_WINDOWPOS_UNDEFINED;

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

extern int new_WINDOW_WIDTH;
extern int new_WINDOW_HEIGHT;

constexpr auto DEFAULT_LOG_LEVEL = Util::Logger::Level::DEBUG;

/**
 * @brief FPS limit
 *
 * Set value to 0 to turn off FPS cap
 */
extern unsigned int FPS_CAP;// = 60;

#endif
