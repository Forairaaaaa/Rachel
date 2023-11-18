/**
 * @file page_sound.cpp
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


void AppSettings::_page_sound()
{
    while (1)
    {
        std::vector<std::string> items = { "[SOUND]" };

        // Get button sound config 
        items.push_back(HAL::GetSystemConfig().volume == 0 ? "Button sound   OFF" : "Button sound    ON");
        items.push_back("Back");

        auto selected = _data.select_menu->waitResult(items);

        // Button sound 
        if (selected == 1)
        {
            HAL::GetSystemConfig().volume = HAL::GetSystemConfig().volume == 0 ? 255 : 0;
            _data.is_config_changed = true;
        }
        else
            break;
    }
}
