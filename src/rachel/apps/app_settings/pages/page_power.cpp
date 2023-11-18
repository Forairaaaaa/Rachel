/**
 * @file page_power.cpp
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


using namespace MOONCAKE::APPS;
using namespace SYSTEM::UI;


void AppSettings::_page_power()
{
    std::vector<std::string> items = {
        "[POWER]",
        "Power Off",
        "Reboot",
        "Back"
    };

    auto selected = _data.select_menu->waitResult(items);
    if (selected == 1)
        HAL::PowerOff();
    else if (selected == 2)
        HAL::Reboot();
}
