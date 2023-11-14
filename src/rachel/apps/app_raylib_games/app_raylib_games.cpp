/**
 * @file app_raylibgames.cpp
 * @author Forairaaaaa
 * @brief Ref: https://www.raylib.com/games.html
 * @version 0.1
 * @date 2023-11-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "app_raylib_games.h"
#include "spdlog/spdlog.h"
#include "../../hal/hal.h"
#include "../assets/theme/theme.h"
#include "../utils/system/ui/ui.h"
#include "games/games.h"


using namespace MOONCAKE::APPS;


void AppRaylibgames::onCreate()
{
    spdlog::info("{} onCreate", getAppName());
}


void AppRaylibgames::onResume()
{
    spdlog::info("{} onResume", getAppName());
}


using namespace SYSTEM::UI;


void AppRaylibgames::onRunning()
{
    auto menu = SelectMenu();

    std::vector<std::string> items = {
        "[RAYLIB GAMES]",
        "Arkanoid",
        "Snake",
        "Tetris",
        "Quit"
    };
    
    auto selected = menu.waitResult(items);

    if (selected == 1)
        ARKANOID::main();

    destroyApp();
}


void AppRaylibgames::onDestroy()
{
    spdlog::info("{} onDestroy", getAppName());
}
