/**
 * @file hal_sdcard.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <mooncake.h>
#include <Arduino.h>
#include <FS.h>
#include <SD.h>
#include "../hal_rachel.h"
#include "../hal_config.h"


void HAL_Rachel::_sdcard_init()
{
    spdlog::info("sd card init");
    HAL_LOG_INFO("sd card init");

    if (!SD.begin(HAL_PIN_SD_CS, SPI))
    {
        spdlog::warn("sd card init failed!");
        HAL_LOG_WARN("sd card init failed!");
        _is_sd_card_ready = false;
        return;
    }

    spdlog::info("sd card size: {}G", SD.cardSize() / 1073741824);
    HAL_LOG_INFO("sd card size: %ldG", SD.cardSize() / 1073741824);
    _is_sd_card_ready = true;
}


void HAL_Rachel::loadTextFont24()
{
    bool ret = _canvas->loadFont("/fonts/font_text_24.vlw", SD);
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
