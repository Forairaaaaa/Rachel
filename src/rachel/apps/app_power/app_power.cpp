/**
 * @file app_power.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "app_power.h"
#include "spdlog/spdlog.h"
#include "../../hal/hal.h"
#include "../assets/theme/theme.h"
#include "../utils/system/ui/ui.h"


using namespace MOONCAKE::APPS;


void AppPower::onCreate()
{
    spdlog::info("{} onCreate", getAppName());
}


void AppPower::onResume()
{
    spdlog::info("{} onResume", getAppName());

    HAL::GetCanvas()->setTextScroll(true);
    HAL::GetCanvas()->setCursor(0, 0);
    HAL::GetCanvas()->clear(THEME_COLOR_LIGHT);
    HAL::LoadTextFont24();
    HAL::GetCanvas()->setTextColor(THEME_COLOR_DARK, THEME_COLOR_LIGHT);
}


using namespace SYSTEM::UI;


void AppPower::onRunning()
{
    auto select_menu = SelectMenu();

    std::vector<std::string> items = {
        "[Power]",
        "Power Off",
        "Reboot",
        "Quit"
    };

    auto result = select_menu.waitResult(items);
    if (result == 1)
        HAL::PowerOff();
    else if (result == 2)
        HAL::Reboot();

    destroyApp();
}


void AppPower::onDestroy()
{
    spdlog::info("{} onDestroy", getAppName());
}
