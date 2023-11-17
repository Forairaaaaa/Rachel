/**
 * @file app_genshin.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "app_genshin.h"
#include "spdlog/spdlog.h"
#include "../../hal/hal.h"
#include "../assets/theme/theme.h"
#include "../utils/system/ui/ui.h"


using namespace MOONCAKE::APPS;


void AppGenshin::onCreate()
{
    spdlog::info("{} onCreate", getAppName());
}


void AppGenshin::onResume()
{
    spdlog::info("{} onResume", getAppName());
}


using namespace SYSTEM::UI;


void AppGenshin::onRunning()
{
    HAL::LoadTextFont24();

    // // Loading 
    // std::vector<std::string> title_list = {"传送松山湖..", "打捞..", "CPU热拔插.."};
    // for (auto& title : title_list)
    // {
    //     for (int i = 10; i <= 110; i += 20)
    //     {
    //         ProgressWindow(title, i);
    //         HAL::CanvasUpdate();
    //         HAL::Delay(100);
    //     }
    // }

    // Launch 
    HAL::GetCanvas()->fillScreen(THEME_COLOR_LIGHT);
    HAL::CanvasUpdate();
    HAL::Delay(2000);

    HAL::GetCanvas()->setTextSize(3);
    HAL::GetCanvas()->drawCenterString("原神", 120, 60);
    HAL::CanvasUpdate();
    HAL::Delay(2000);

    HAL::GetCanvas()->setTextSize(1);
    HAL::GetCanvas()->fillScreen(THEME_COLOR_LIGHT);
    HAL::GetCanvas()->setCursor(32, HAL::GetCanvas()->height() / 3);
    std::vector<std::string> item_list = {"火", "水", "风", "雷", "草", "冰"};
    for (auto& i : item_list)
    {
        HAL::GetCanvas()->print(i.c_str());
        HAL::CanvasUpdate();
        HAL::Delay(400);
    }

    int cursor_x = HAL::GetCanvas()->getCursorX();
    int cursor_y = HAL::GetCanvas()->getCursorY();

    HAL::GetCanvas()->print("岩");
    HAL::GetCanvas()->fillRect(cursor_x + 12, cursor_y, 24, 24, THEME_COLOR_LIGHT);
    HAL::CanvasUpdate();
    HAL::Delay(2000);

    HAL::GetCanvas()->setCursor(cursor_x, cursor_y);
    HAL::GetCanvas()->print("岩");
    HAL::CanvasUpdate();
    HAL::Delay(1000);

    HAL::PopFatalError("你在期待什么? O.o");


    destroyApp();
}


void AppGenshin::onDestroy()
{
    spdlog::info("{} onDestroy", getAppName());
}
