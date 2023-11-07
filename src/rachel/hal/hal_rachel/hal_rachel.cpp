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
#ifdef ESP_PLATFORM
#include <mooncake.h>
#include "hal_rachel.h"
#include <Arduino.h>


void HAL_Rachel::init()
{
    _disp_init();
    _fs_init();
    _gamepad_init();
}


#endif
