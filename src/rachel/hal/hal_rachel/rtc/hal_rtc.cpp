/**
 * @file hal_rtc.cpp
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


void HAL_Rachel::_rtc_init()
{
    spdlog::info("rtc init");

    _rtc = new m5::RTC8563_Class(0x51, 400000, _i2c_bus);
    if (!_rtc->begin())
        spdlog::error("rtc init failed!");


    // // Test 
    // tm set_time;
    // set_time.tm_year = 2023;
    // set_time.tm_mon = 11;
    // set_time.tm_mday = 8;
    // set_time.tm_wday = 6;
    // set_time.tm_hour = 22;
    // set_time.tm_min = 33;
    // set_time.tm_sec = 44;
    // this->setDateTime(set_time);

    // m5::rtc_time_t time;
    // m5::rtc_date_t date;
    // while (1)
    // {
    //     _rtc->getTime(&time);
    //     _rtc->getDate(&date);
    //     printf("%02d:%02d:%02d %04d,%02d,%02d,%02d\n",
    //         time.hours,
    //         time.minutes,
    //         time.seconds,
    //         date.year,
    //         date.month,
    //         date.date,
    //         date.weekDay
    //     );
    //     this->delay(1000);
    // }
}


void HAL_Rachel::setDateTime(tm dateTime)
{
    _rtc->setDateTime(dateTime);
}


tm& HAL_Rachel::dateTime()
{
    _date_time = _rtc->getDateTime().get_tm();
    return _date_time;
}
