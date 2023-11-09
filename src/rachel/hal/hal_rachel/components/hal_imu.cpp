/**
 * @file hal_imu.cpp
 * @author Forairaaaaa
 * @brief Ref: https://github.com/m5stack/M5Unified
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


void HAL_Rachel::_imu_init()
{
    spdlog::info("imu init");
    HAL_LOG_INFO("imu init");
    
    _imu = new m5::IMU_Class();
    if (!_imu->begin(_i2c_bus))
    {
        spdlog::error("imu init failed!");
        HAL_LOG_ERROR("imu init failed!");
    }
        

    // // Test
    // while (1)
    // {
    //     auto imu_update = _imu->update();
    //     if (imu_update)
    //     {
    //         // Obtain data on the current value of the IMU.
    //         auto data = _imu->getImuData();
    //         printf("%f\t%f\t%f\n", data.accel.x, data.accel.y, data.accel.z);
    //     }
    //     delay(50);
    // }
}


void HAL_Rachel::updateImuData()
{
    auto imu_update = _imu->update();
    if (imu_update)
    {
        // Obtain data on the current value of the IMU.
        auto data = _imu->getImuData();
        _imu_data.accelX = data.accel.x;
        _imu_data.accelY = data.accel.y;
        _imu_data.accelZ = data.accel.z;
    }
}
