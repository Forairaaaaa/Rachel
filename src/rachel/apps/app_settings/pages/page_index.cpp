/**
 * @file page_index.cpp
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


using namespace MOONCAKE::APPS;
using namespace SYSTEM::UI;


void AppSettings::_page_index()
{
    std::vector<std::string> items = {
        "[SETTINGS]",
        "Power",
        "Display",
        "Sound",
        "Time",
        "About",
        "Quit"
    };

    while (1)
    {
        auto selected = _data.select_menu->waitResult(items);

        if (selected == 1)
            _page_power();
        else if (selected == 2)
            _page_display();
        else if (selected == 3)
            _page_sound();
        else if (selected == 4)
            _page_time();
        else if (selected == 5)
            _page_about();
        else
            break;
    }
}
