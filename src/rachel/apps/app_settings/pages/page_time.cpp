/**
 * @file page_time.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../app_settings.h"
#include "../../utils/system/ui/ui.h"
#include "../../../hal/hal.h"
#include "spdlog/spdlog.h"
#include <cstring>
#include <string>


using namespace MOONCAKE::APPS;
using namespace SYSTEM::UI;


static void _handle_set_time(SelectMenu* selectMenu)
{
    // Get current time
    tm time_buffer;
    std::memcpy(&time_buffer, HAL::GetLocalTime(), sizeof(tm));

    // Hour 
    std::vector<std::string> items = { "[SET HOUR]" };
    for (int i = 0; i < 24; i++)
        items.push_back(std::to_string(i));

    auto selected = selectMenu->waitResult(items);
    time_buffer.tm_hour = selected - 1;

    // Minute 
    items.clear();
    items.push_back("[SET MINUTE]");
    for (int i = 0; i < 60; i++)
        items.push_back(std::to_string(i));

    selected = selectMenu->waitResult(items);
    time_buffer.tm_min = selected - 1;

    // Second  
    items.clear();
    items.push_back("[SET SECOND]");
    for (int i = 0; i < 60; i++)
        items.push_back(std::to_string(i));

    selected = selectMenu->waitResult(items);
    time_buffer.tm_sec = selected - 1;

    // Confirm 
    char string_buffer[10];
    strftime(string_buffer, 10, "%X", &time_buffer);

    items.clear();
    items.push_back("[SURE?]");
    items.push_back("Set time: " + std::string(string_buffer));
    items.push_back("Cancel");

    selected = selectMenu->waitResult(items);
    if (selected == 1)
        HAL::SetSystemTime(time_buffer);
}


static void _handle_set_date(SelectMenu* selectMenu)
{
    // Get current time
    tm time_buffer;
    std::memcpy(&time_buffer, HAL::GetLocalTime(), sizeof(tm));

    // Year
    std::vector<std::string> items = { "[SET YEAR]" };
    for (int i = 2023; i < 2078; i++)
        items.push_back(std::to_string(i));

    auto selected = selectMenu->waitResult(items);
    // tm_year = selected - 1 + 2023 - 1900
    time_buffer.tm_year = selected + 122;
    // spdlog::info("year: {}", time_buffer.tm_year);

    // Month 
    items.clear();
    items.push_back("[SET MONTH]");
    for (int i = 1; i < 13; i++)
        items.push_back(std::to_string(i));

    selected = selectMenu->waitResult(items);
    time_buffer.tm_mon = selected - 1;
    // spdlog::info("mon: {}", time_buffer.tm_mon);

    //  Month day 
    items.clear();
    items.push_back("[SET MONTH DAY]");
    for (int i = 1; i < 32; i++)
        items.push_back(std::to_string(i));

    selected = selectMenu->waitResult(items);
    time_buffer.tm_mday = selected;
    // spdlog::info("mday: {}", time_buffer.tm_year);

    // Confirm 
    char string_buffer[10];
    strftime(string_buffer, 10, "%x", &time_buffer);

    items.clear();
    items.push_back("[SURE?]");
    items.push_back("Set date: " + std::string(string_buffer));
    items.push_back("Cancel");

    selected = selectMenu->waitResult(items);
    if (selected == 1)
    {
        // Update latest time 
        time_buffer.tm_hour = HAL::GetLocalTime()->tm_hour;
        time_buffer.tm_min = HAL::GetLocalTime()->tm_min;
        time_buffer.tm_sec = HAL::GetLocalTime()->tm_sec;

        HAL::SetSystemTime(time_buffer);
    }
}


static void _handle_set_weekday(SelectMenu* selectMenu)
{
    // Get current time
    tm time_buffer;
    std::memcpy(&time_buffer, HAL::GetLocalTime(), sizeof(tm));

    char string_buffer[10];
    std::vector<std::string> items = { "[SET WEEKDAY]" };
    for (int i = 0; i < 7; i++)
    {
        time_buffer.tm_wday = i;
        strftime(string_buffer, 10, "%A", &time_buffer);
        items.push_back(string_buffer);
    }

    auto selected = selectMenu->waitResult(items);
    time_buffer.tm_wday = selected - 1;

    // Confirm 
    strftime(string_buffer, 10, "%A", &time_buffer);
    
    items.clear();
    items.push_back("[SURE?]");
    items.push_back("Set: " + std::string(string_buffer));
    items.push_back("Cancel");

    selected = selectMenu->waitResult(items);
    if (selected == 1)
    {
        // Update latest time 
        time_buffer.tm_hour = HAL::GetLocalTime()->tm_hour;
        time_buffer.tm_min = HAL::GetLocalTime()->tm_min;
        time_buffer.tm_sec = HAL::GetLocalTime()->tm_sec;

        HAL::SetSystemTime(time_buffer);
    }
}


void AppSettings::_page_time()
{
    while (1)
    {
        std::vector<std::string> items = { 
            "[TIME]",
            "Set time",
            "Set date",
            "Set weekday",
            "Back"
        };

        auto selected = _data.select_menu->waitResult(items);

        // Button sound 
        if (selected == 1)
            _handle_set_time(_data.select_menu);
        else if (selected == 2)
            _handle_set_date(_data.select_menu);
        else if (selected == 3)
            _handle_set_weekday(_data.select_menu);
        else
            break;
    }
}