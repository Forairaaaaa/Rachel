/**
 * @file app_screencast.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-04
 * Ref: https://github.com/lovyan03/ESP32_ScreenShotReceiver
 * @copyright Copyright (c) 2023
 * 
 */
#include "app_screencast.h"
#include "spdlog/spdlog.h"
#include "../../hal/hal.h"
#include "../assets/theme/theme.h"
#include "../utils/system/ui/progress_window/progress_window.h"

// Not enough ram, enable this arduino wifi shit cause font loading from sd card filed 
// push png filed, nofrendo load rom loading failed 
#define ENABLE_APP_SCREENCAST   0

#ifdef ESP_PLATFORM
#if ENABLE_APP_SCREENCAST
#include <Arduino.h>
#include <WiFi.h>
#include "screen_shot_receiver/TCPReceiver.h"
#endif
#endif


using namespace MOONCAKE::APPS;
using namespace SYSTEM::UI;


void AppScreencast::onCreate()
{
    spdlog::info("{} onCreate", getAppName());
}


void AppScreencast::onResume()
{
    spdlog::info("{} onResume", getAppName());
    
}


#ifdef ESP_PLATFORM
// Not enough ram, linking this arduino wifi shit cause font loading from sd card filed 
// push png filed, nofrendo load rom loading failed 
void AppScreencast::onRunning()
{
    #if ENABLE_APP_SCREENCAST
    HAL::LoadTextFont24();

    // 接続できるまで10秒待機
    spdlog::info("try connect wifi in nvs");
    WiFi.mode(WIFI_MODE_STA);
    WiFi.begin();
    for (int i = 0; WiFi.status() != WL_CONNECTED && i < 100; i++) 
    {
        delay(100);
        if (HAL::GetButton(GAMEPAD::BTN_SELECT))
            HAL::Reboot();
        
        ProgressWindow("尝试连接WiFi..", i);
        HAL::CanvasUpdate();
    }


    HAL::GetCanvas()->fillScreen(THEME_COLOR_DARK);
    HAL::GetCanvas()->setTextColor(THEME_COLOR_LIGHT, THEME_COLOR_DARK);

    // 接続できない場合はSmartConfigを起動
    // https://itunes.apple.com/app/id1071176700
    // https://play.google.com/store/apps/details?id=com.cmmakerclub.iot.esptouch
    if (WiFi.status() != WL_CONNECTED) 
    {
        spdlog::info("start smart config");
        WiFi.mode(WIFI_MODE_APSTA);
        WiFi.beginSmartConfig();

        HAL::GetCanvas()->drawCenterString("等待SmartConfig配网",  120, 120 - 48);
        HAL::CanvasUpdate();
        while (WiFi.status() != WL_CONNECTED) 
        {
            delay(100);
            if (HAL::GetButton(GAMEPAD::BTN_SELECT))
                HAL::Reboot();
        }
        WiFi.stopSmartConfig();
        WiFi.mode(WIFI_MODE_STA);
    }


    HAL::GetCanvas()->fillScreen(THEME_COLOR_DARK);
    HAL::GetCanvas()->drawCenterString("已连接",  120, 120 - 48);
    String ip = "IP: ";
    ip += WiFi.localIP().toString();
    HAL::GetCanvas()->drawCenterString(ip.c_str(), 122, 120 - 12);
    HAL::CanvasUpdate();
    

    auto recv = new TCPReceiver;
    recv->setup(HAL::GetDisplay());
    while (1)
    {
        recv->loop();
        if (HAL::GetButton(GAMEPAD::BTN_SELECT))
                HAL::Reboot();
    }
    delete recv;
    #endif


    destroyApp();
}
#else

void AppScreencast::onRunning()
{
    HAL::PopFatalError("懒得抽象了");
}

#endif


void AppScreencast::onDestroy()
{
    spdlog::info("{} onDestroy", getAppName());
}
