/**
 * @file hal_gamepad.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <mooncake.h>
#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>
#include "../hal_rachel.h"
#include "../hal_config.h"


void HAL_Rachel::_fs_init()
{
    spdlog::info("fs init");
    HAL_LOG_INFO("fs init");

    // File system 
    if (!LittleFS.begin(true)) 
    {
        spdlog::error("LittleFS init failed!");
        popFatalError("LittleFS init failed");
    }
}


void HAL_Rachel::loadTextFont24()
{
    bool ret = _canvas->loadFont("/_sys/fonts/zpix_cn_24.vlw", LittleFS);
    if (!ret)
    {
        spdlog::error("load font failed");
        _canvas->setFont(&fonts::efontCN_24);
    }
    _canvas->setTextSize(1);
}


void HAL_Rachel::loadTextFont16()
{
    // _canvas->setFont(&fonts::efontCN_16);
    // _canvas->setTextSize(1);
}


void HAL_Rachel::loadLauncherFont24()
{
    // // 27fps, 37ms/f
    // loadTextFont24();

    // 40fps, 25ms/f
    _canvas->setFont(&fonts::efontCN_24);
    _canvas->setTextSize(1);
}
