/**
 * @file hal_rtc.cpp
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


void HAL_Rachel::_rtc_init()
{
    spdlog::info("rtc init");

    _rtc = new m5::RTC8563_Class(0x51, 400000, _i2c_bus);
    if (!_rtc->begin())
        spdlog::error("rtc init failed!");

    _adjust_sys_time();
    

    // // Test 
    // tm set_time;
    // set_time.tm_year = 2023;
    // set_time.tm_mon = 10;
    // set_time.tm_mday = 8;
    // set_time.tm_wday = 3;
    // set_time.tm_hour = 16;
    // set_time.tm_min = 15;
    // set_time.tm_sec = 0;
    // this->setDateTime(set_time);

    // m5::rtc_time_t rtc_time;
    // m5::rtc_date_t rtc_date;
    // while (1)
    // {
    //     _rtc->getTime(&rtc_time);
    //     _rtc->getDate(&rtc_date);
    //     printf("%02d:%02d:%02d %04d,%02d,%02d,%02d\n",
    //         rtc_time.hours,
    //         rtc_time.minutes,
    //         rtc_time.seconds,
    //         rtc_date.year,
    //         rtc_date.month,
    //         rtc_date.date,
    //         rtc_date.weekDay
    //     );
    //     this->delay(1000);
    // }
}


void HAL_Rachel::setSystemTime(tm dateTime)
{
    _rtc->setDateTime(dateTime);
    _adjust_sys_time();
}


void HAL_Rachel::_adjust_sys_time()
{
    auto time = _rtc->getDateTime().get_tm();
    time_t tv_sec = mktime(&time);
    struct timeval now = { .tv_sec = tv_sec };
    settimeofday(&now, NULL);
    spdlog::info("adjusted system time to rtc");
}
