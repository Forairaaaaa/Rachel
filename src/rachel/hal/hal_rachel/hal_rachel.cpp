/**
 * @file hal_rachel.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <mooncake.h>
#include "hal_rachel.h"
#include <Arduino.h>
#include "hal_config.h"


void HAL_Rachel::init()
{
    _power_init();
    _disp_init();
    _fs_init();
    _gamepad_init();
    _i2c_init();
    _rtc_init();
}

