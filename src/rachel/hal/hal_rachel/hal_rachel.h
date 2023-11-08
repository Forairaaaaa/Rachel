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
#include "rtc/RTC8563_Class.hpp"
#include "imu/IMU_Class.hpp"


class HAL_Rachel : public HAL
{
private:
    std::array<uint8_t, 11> _gamepad_key_map;
    m5::I2C_Class* _i2c_bus;
    m5::RTC8563_Class* _rtc;
    m5::IMU_Class* _imu;

private:
    void _power_init();
    void _disp_init();
    void _fs_init();
    void _gamepad_init();
    void _i2c_init();
    void _rtc_init();
    void _imu_init();

public:
    HAL_Rachel() :
        _i2c_bus(nullptr),
        _rtc(nullptr),
        _imu(nullptr)
        {}
    ~HAL_Rachel()
    {
        delete _rtc;
        delete _imu;
        delete _i2c_bus;
    }

    inline std::string type() override { return "Rachel"; }

    inline void init() override
    {
        _power_init();
        _disp_init();
        _fs_init();
        _gamepad_init();
        _i2c_init();
        _rtc_init();
        _imu_init();
    }

    void loadSystemFont24() override;
    bool getButton(GAMEPAD::GamePadButton_t button) override;
    void powerOff() override;
    void setDateTime(tm dateTime) override;
    tm& dateTime() override;
};
