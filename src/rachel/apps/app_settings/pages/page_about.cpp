/**
 * @file page_about.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../app_settings.h"
#include "../../../hal/hal.h"
#include "../assets/page_about_png.hpp"


using namespace MOONCAKE::APPS;


void AppSettings::_page_about()
{
    HAL::GetCanvas()->drawPng(page_about_png, page_about_png_size);
    HAL::CanvasUpdate();

    while (1)
    {
        if (HAL::GetAnyButton())
        {
            while (HAL::GetAnyButton())
                HAL::Delay(50);
            break;
        }
        HAL::Delay(50);
    }
}
