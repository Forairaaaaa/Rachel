/**
 * @file app_gbemulator.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "app_gbemulator.h"
#include "spdlog/spdlog.h"
#include "../../hal/hal.h"
#include "../assets/theme/theme.h"
#include "utils/gb_emulator/gb_emulator.hpp"


using namespace MOONCAKE::APPS;


void AppGbemulator::onCreate()
{
    spdlog::info("{} onCreate", getAppName());
}


void AppGbemulator::onResume()
{
    spdlog::info("{} onResume", getAppName());

    HAL::GetCanvas()->setTextScroll(true);
    HAL::GetCanvas()->setCursor(0, 0);
    HAL::GetCanvas()->clear(THEME_COLOR_LIGHT);
    HAL::LoadTextFont24();
    HAL::GetCanvas()->setTextColor(THEME_COLOR_DARK, THEME_COLOR_LIGHT);

    gb_emulator_start();
}


void AppGbemulator::onRunning()
{
    gb_emulator_update();
}


void AppGbemulator::onDestroy()
{
    spdlog::info("{} onDestroy", getAppName());
}
