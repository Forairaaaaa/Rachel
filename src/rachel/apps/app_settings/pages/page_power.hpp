/**
 * @file page_power.hpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../../utils/system/ui/ui.h"
#include "../../../hal/hal.h"


using namespace SYSTEM::UI;


void page_power(SelectMenu& selectMenu)
{
    std::vector<std::string> items = {
        "[POWER]",
        "Power Off",
        "Reboot",
        "Back"
    };

    auto selected = selectMenu.waitResult(items);
    if (selected == 1)
        HAL::PowerOff();
    else if (selected == 2)
        HAL::Reboot();
}
