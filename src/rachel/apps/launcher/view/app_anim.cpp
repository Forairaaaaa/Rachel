/**
 * @file app_anim.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../launcher.h"
#include "menu_render_callback.hpp"


using namespace MOONCAKE::APPS;


void Launcher::_play_app_anim(bool open)
{
    if (open)
        _data.app_anim.setAnim(LVGL::ease_out, THEME_APP_ICON_WIDTH, 320, 360);
    else 
        _data.app_anim.setAnim(LVGL::ease_out, 320, THEME_APP_ICON_WIDTH, 360);

    _data.app_anim.resetTime(HAL::Millis());

    int anim_value = 0;
    int offset = 0;
    while (!_data.app_anim.isFinished(HAL::Millis()))
    {
        if (!open)
            _data.menu->update(HAL::Millis());

        anim_value = _data.app_anim.getValue(HAL::Millis());
        offset = anim_value / 2;
        HAL::GetCanvas()->fillSmoothRoundRect(
            120 - offset, 
            THEME_APP_ICON_MARGIN_TOP + THEME_APP_ICON_HEIGHT_HALF - offset, 
            anim_value,
            anim_value,
            60,
            THEME_COLOR_LIGHT
        );

        HAL::CanvasUpdate();
    }
}

