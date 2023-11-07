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
#include "../hal_rachel.h"
#include <Arduino.h>


void HAL_Rachel::_fs_init()
{
    
}

void HAL_Rachel::loadSystemFont24()
{
    GetCanvas()->setFont(&fonts::efontCN_24);
}

