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
#include "utils/m5unified/I2C_Class.hpp"
#include "utils/m5unified/RTC8563_Class.hpp"
#include "utils/m5unified/IMU_Class.hpp"
#include "utils/m5unified/Speaker_Class.hpp"


class HAL_Rachel : public HAL
{
private:
    std::array<uint8_t, 11> _gamepad_key_map;
    m5::I2C_Class* _i2c_bus;
    m5::RTC8563_Class* _rtc;
    m5::IMU_Class* _imu;
    m5::Speaker_Class* _spk;

private:
    void _power_init();
    void _disp_init();
    void _disp_logo();
    void _fs_init();
    void _i2c_init();
    void _rtc_init();
    void _imu_init();
    void _spk_init();
    void _sdcard_init();
    void _gamepad_init();
    void _adjust_sys_time();
    void _sum_up();

public:
    HAL_Rachel() :
        _i2c_bus(nullptr),
        _rtc(nullptr),
        _imu(nullptr),
        _spk(nullptr)
        {}
    ~HAL_Rachel()
    {
        delete _rtc;
        delete _imu;
        delete _i2c_bus;
        delete _spk;
    }

    inline std::string type() override { return "Rachel"; }

    inline void init() override
    {
        _power_init();
        _disp_init();
        _gamepad_init();
        _spk_init();
        _i2c_init();
        _rtc_init();
        _imu_init();
        _fs_init();
        _sdcard_init();
        _sum_up();
    }

    void reboot() override;
    void loadTextFont24() override;
    void loadTextFont16() override;
    void loadLauncherFont24() override;

    bool getButton(GAMEPAD::GamePadButton_t button) override;
    void powerOff() override;
    void setSystemTime(tm dateTime) override;
    void updateImuData() override;
    void beep(float frequency, uint32_t duration) override;
    void setBeepVolume(uint8_t volume) override;
};
