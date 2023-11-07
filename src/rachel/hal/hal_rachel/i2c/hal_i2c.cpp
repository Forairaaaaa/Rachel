/**
 * @file hal_i2c.cpp
 * @author Forairaaaaa
 * @brief Ref: https://github.com/m5stack/M5Unified
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


void HAL_Rachel::_i2c_init()
{
    spdlog::info("i2c bus init");

    // Init bus 
    _i2c_bus = new m5::I2C_Class;
    _i2c_bus->begin(I2C_NUM_0, HAL_PIN_I2C_SDA, HAL_PIN_I2C_SCL);

    // Scan 
    bool scan_list[120];
    _i2c_bus->scanID(scan_list);
    for (int i = 8; i < 0x78; i++)
    {
        if (scan_list[i])
            spdlog::info("i2c bus scan get: 0x{0:x}", i);
    }
}
