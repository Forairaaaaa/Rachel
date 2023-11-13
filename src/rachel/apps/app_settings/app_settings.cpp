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
#include "pages/page_index.hpp"


using namespace MOONCAKE::APPS;


void AppSettings::onCreate()
{
    spdlog::info("{} onCreate", getAppName());
}


void AppSettings::onResume()
{
    spdlog::info("{} onResume", getAppName());
}


void AppSettings::onRunning()
{
    auto menu_menu = SelectMenu();
    page_index(menu_menu);
    destroyApp();
}


void AppSettings::onDestroy()
{
    spdlog::info("{} onDestroy", getAppName());
}
