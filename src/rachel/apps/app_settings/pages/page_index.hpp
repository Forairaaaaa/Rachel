/**
 * @file page_index.hpp
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
#include "page_power.hpp"


using namespace SYSTEM::UI;


void page_index(SelectMenu& selectMenu)
{
    std::vector<std::string> items = {
        "[SETTINGS]",
        "Power",
        "Time",
        "About",
        "Quit"
    };

    while (1)
    {
        auto selected = selectMenu.waitResult(items);

        if (selected == 1)
            page_power(selectMenu);
        else
            break;
    }
}
