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
#include "../hal_rachel.h"
#include "../hal_config.h"
#include <Arduino.h>
#include <SD.h>


void HAL_Rachel::_sdcard_init()
{
    spdlog::info("sd card init");

    if (!SD.begin(HAL_PIN_SD_CS, SPI))
    {
        spdlog::warn("sd card init failed!");
        _is_sd_card_ready = false;
        return;
    }

    spdlog::info("sd card size: {}G", SD.cardSize() / 1073741824);
    _is_sd_card_ready = true;
}
