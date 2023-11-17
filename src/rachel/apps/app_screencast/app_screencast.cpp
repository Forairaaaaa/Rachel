/**
 * @file app_screencast.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "app_screencast.h"
#include "spdlog/spdlog.h"
#include "../../hal/hal.h"
#include "../assets/theme/theme.h"
#include "../utils/system/ui/ui.h"


using namespace MOONCAKE::APPS;


void AppScreencast::onCreate()
{
    spdlog::info("{} onCreate", getAppName());
}


void AppScreencast::onResume()
{
    spdlog::info("{} onResume", getAppName());

    HAL::GetCanvas()->setTextScroll(true);
    HAL::GetCanvas()->setCursor(0, 0);
    HAL::GetCanvas()->clear(THEME_COLOR_LIGHT);
    HAL::LoadTextFont24();
    HAL::GetCanvas()->setTextColor(THEME_COLOR_DARK, THEME_COLOR_LIGHT);
}


using namespace SYSTEM::UI;


void AppScreencast::onRunning()
{
    // // Every seconds 
    // if ((HAL::Millis() - _data.count) > 1000)
    // {
    //     spdlog::info("{}: Hi", getAppName());

        
    //     HAL::GetCanvas()->printf(" Hi!");
    //     HAL::CanvasUpdate();


    //     _data.count = HAL::Millis();
    // }


    // // Press Select to quit  
    // if (HAL::GetButton(GAMEPAD::BTN_SELECT))
    //     destroyApp();


    HAL::LoadTextFont24();
    for (int i = 0; i < 100; i++)
    {
        ProgressWindow("正在检测智商..", i);
        HAL::CanvasUpdate();
        HAL::Delay(50);
    }

    for (int i = 0; i < 100; i++)
    {
        ProgressWindow("啊?", i, true);
        HAL::CanvasUpdate();
        HAL::Delay(50);
    }



    destroyApp();
}


void AppScreencast::onDestroy()
{
    spdlog::info("{} onDestroy", getAppName());
}
