/**
 * @file hal_rachel.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../hal.h"
#include "i2c/I2C_Class.hpp"


class HAL_Rachel : public HAL
{
private:
    std::array<uint8_t, 11> _gamepad_key_map;
    m5::I2C_Class* _i2c_bus;

private:
    void _power_init();
    void _disp_init();
    void _fs_init();
    void _gamepad_init();
    void _i2c_init();
    void _rtc_init();

public:
    HAL_Rachel() :
        _i2c_bus(nullptr)
        {}

    std::string type() override { return "Rachel"; }
    void init() override;
    void loadSystemFont24() override;
    bool getButton(GAMEPAD::GamePadButton_t button) override;
    void powerOff() override;
};
