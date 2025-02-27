#ifndef CONFIG_H
#define CONFIG_H

#include "pch.hpp" // IWYU pragma: export

#include "Util/Logger.hpp"

constexpr const char *TITLE = "Practical Tools for Simple Design";

static int WINDOW_POS_X = SDL_WINDOWPOS_UNDEFINED;
static int WINDOW_POS_Y = SDL_WINDOWPOS_UNDEFINED;

static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 600;

constexpr Util::Logger::Level DEFAULT_LOG_LEVEL = Util::Logger::Level::DEBUG;

/**
 * @brief FPS limit
 *
 * Set value to 0 to turn off FPS cap
 */
static unsigned int FPS_CAP = 60;

#endif
