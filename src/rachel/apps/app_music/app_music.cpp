/**
 * @file app_music.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "app_music.h"
#include "spdlog/spdlog.h"
#include "../../hal/hal.h"
#include "../assets/theme/theme.h"
#include "../utils/system/ui/ui.h"


using namespace MOONCAKE::APPS;


void AppMusic::onCreate()
{
    spdlog::info("{} onCreate", getAppName());
}


void AppMusic::onResume()
{
    spdlog::info("{} onResume", getAppName());

    HAL::GetCanvas()->setTextScroll(true);
    HAL::GetCanvas()->setCursor(0, 0);
    HAL::GetCanvas()->clear(THEME_COLOR_LIGHT);
    HAL::LoadTextFont24();
    HAL::GetCanvas()->setTextColor(THEME_COLOR_DARK, THEME_COLOR_LIGHT);
}


using namespace SYSTEM::UI;


void AppMusic::onRunning()
{
    // // Every seconds 
    // if ((HAL::Millis() - _data.count) > 1000)
    // {
    //     spdlog::info("{}: Hi", getAppName());

        
    //     HAL::GetCanvas()->printf(" Hi!");
    //     HAL::CanvasUpdate();


    //     _data.count = HAL::Millis();
    // }


    // // Press Select to quit  
    // if (HAL::GetButton(GAMEPAD::BTN_SELECT))
    //     destroyApp();


    




    auto select_menu = SelectMenu();

    std::vector<std::string> test = {
        "[MENU TYPE]",
        "Left",
        "Center",
        "Right",
        "Settings",
        "Quit"
    };

    std::vector<std::string> settings = {
        "[SETTINGS]",
        "asdasdasd",
        "9879ht",
        "5465gmiokn",
        "1221d3ffff",
        "-=-=--=-dd",
        "00000000",
        ":)",
        "-=-=--=-dd",
        "00000000",
        ":)",
        "Back"
    };

    auto alignment = SelectMenu::ALIGN_LEFT;
    while (1)
    {
        auto result = select_menu.waitResult(test, alignment);

        if (result == 1)
            alignment = SelectMenu::ALIGN_LEFT;
        else if (result == 2)
            alignment = SelectMenu::ALIGN_CENTER;
        else if (result == 3)
            alignment = SelectMenu::ALIGN_RIGHT;

        else if (result == 4)
        {
            while (1)
            {
                result = select_menu.waitResult(settings, alignment);
                if (result == settings.size() - 1)
                    break;
            }
        }

        else
            break;
    }


    destroyApp();
}


void AppMusic::onDestroy()
{
    spdlog::info("{} onDestroy", getAppName());
}
