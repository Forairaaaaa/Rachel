/**
 * @file app_nofrendo.cpp
 * @author Forairaaaaa
 * @brief Ref: https://github.com/pebri86/esplay-retro-emulation/tree/master
 * @version 0.1
 * @date 2023-11-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "app_nofrendo.h"
#include "spdlog/spdlog.h"
#include "../../hal/hal.h"
#include "../assets/theme/theme.h"
extern "C"
{
    #include "nofrendo/nofrendo.h"
}


using namespace MOONCAKE::APPS;


void AppNofrendo::onCreate()
{
    spdlog::info("{} onCreate", getAppName());
}


void AppNofrendo::onResume()
{
    spdlog::info("{} onResume", getAppName());
    HAL::GetCanvas()->fillScreen(TFT_BLACK);
    HAL::CanvasUpdate();
}


void AppNofrendo::onRunning()
{
    nofrendo_main(0, NULL);
}


void AppNofrendo::onDestroy()
{
    spdlog::info("{} onDestroy", getAppName());
}
