/**
 * @file page_display.cpp
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
#include "../../utils//system/inputs/inputs.h"
#include "../../../hal/hal.h"
#include "spdlog/spdlog.h"
#include <cstdint>
#include <string>


using namespace MOONCAKE::APPS;
using namespace SYSTEM::UI;
using namespace SYSTEM::INPUTS;


static void _handle_brightness_config()
{
    // 15~255 16/step 
    int brightness = HAL::GetDisplay()->getBrightness();
    bool is_changed = true;

    Button btn_left(GAMEPAD::BTN_LEFT);
    Button btn_right(GAMEPAD::BTN_RIGHT);
    Button btn_ok(GAMEPAD::BTN_A);

    std::string title;
    while (1)
    {
        // Render brightness bar 
        if (is_changed)
        {
            is_changed = false;

            // Apply change 
            HAL::GetSystemConfig().brightness = brightness;
            HAL::GetDisplay()->setBrightness(HAL::GetSystemConfig().brightness);

            // Render brightness setting bar 
            title = "Brightness " + std::to_string(brightness);
            ProgressWindow(title, brightness * 100 / 255);
            HAL::CanvasUpdate();
        }
        else
        {
            HAL::Delay(20);
        }

        // Read input 
        if (btn_left.pressed())
        {
            brightness -= 16;
            if (brightness < 16)
                brightness = 16;
            is_changed = true;
        }
        else if (btn_right.pressed())
        {
            brightness += 16;
            if (brightness > 255)
                brightness = 255;
            is_changed = true;
        }
        else if (btn_ok.released())
        {
            break;
        }
    }
}


void AppSettings::_page_display()
{
    while (1)
    {
        std::vector<std::string> items = { "[DISPLAY]" };

        // Get button sound config 
        items.push_back("Brightness     " + std::to_string(HAL::GetSystemConfig().brightness));
        items.push_back("Back");

        auto selected = _data.select_menu->waitResult(items);

        // Brightness 
        if (selected == 1)
        {
            _handle_brightness_config();
            _data.is_config_changed = true;
        }
        else
            break;
    }
}
