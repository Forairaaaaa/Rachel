/**
 * @file app_settings.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "app_settings.h"
#include "spdlog/spdlog.h"
#include "../../hal/hal.h"
#include "../assets/theme/theme.h"


using namespace MOONCAKE::APPS;
using namespace SYSTEM::UI;


void AppSettings::onCreate()
{
    spdlog::info("{} onCreate", getAppName());
    _data.select_menu = new SelectMenu;
}


void AppSettings::onResume()
{
    spdlog::info("{} onResume", getAppName());
}


void AppSettings::onRunning()
{
    // Create menu and load pages 
    _page_index();

    // If config changed 
    if (_data.is_config_changed)
    {
        std::vector<std::string> items = {
            "[SAVE CHANGES?]",
            "Yes",
            "No"
        };
        auto selected_item = _data.select_menu->waitResult(items);
        if (selected_item == 1)
            HAL::SaveSystemConfig();
    }

    destroyApp();
}


void AppSettings::onDestroy()
{
    delete _data.select_menu;
    spdlog::info("{} onDestroy", getAppName());
}
