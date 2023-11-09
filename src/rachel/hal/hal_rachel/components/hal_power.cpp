/**
 * @file hal_power.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <mooncake.h>
#include "../hal_rachel.h"
#include <Arduino.h>
#include "../hal_config.h"


void HAL_Rachel::_power_init()
{
    // Hold power 
    gpio_reset_pin((gpio_num_t)HAL_PIN_PWR_HOLD);
    pinMode(HAL_PIN_PWR_HOLD, OUTPUT);
    digitalWrite(HAL_PIN_PWR_HOLD, 1);
}


void HAL_Rachel::powerOff()
{
    digitalWrite(HAL_PIN_PWR_HOLD, 0);
    delay(1000);
}


void HAL_Rachel::reboot()
{
    esp_restart();
}
