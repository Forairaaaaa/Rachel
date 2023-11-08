/**
 * @file hal_speaker.cpp
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
#include <Arduino.h>
#include "../hal_config.h"


void HAL_Rachel::_spk_init()
{
    spdlog::info("buzz init");

    _spk = new m5::Speaker_Class;
    auto cfg = _spk->config();
    cfg.buzzer = true;
    cfg.pin_data_out = HAL_PIN_BUZZ;
    _spk->config(cfg);

    if (!_spk->begin())
        spdlog::error("buzz init failed!");


    // // Test
    // _spk->tone(4000, 300);
    // while (_spk->isPlaying())
    //     delay(20);
    // delay(1000);
    // _spk->tone(6000, 300);
    // while (_spk->isPlaying())
    //     delay(20);

    // _spk->setVolume(255);
    // delay(1000);

    // _spk->tone(4000, 300);
    // while (_spk->isPlaying())
    //     delay(20);
    // delay(1000);
    // _spk->tone(6000, 300);
    // while (_spk->isPlaying())
    //     delay(20);
}


void HAL_Rachel::beep(float frequency, uint32_t duration)
{
    _spk->tone(frequency, duration);
}


void HAL_Rachel::setBeepVolume(uint8_t volume)
{
    _spk->setVolume(volume);
}
