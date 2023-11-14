/**
 * @file hal_simulator.hpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#ifndef ESP_PLATFORM
#include "lgfx/v1/LGFX_Sprite.hpp"
#include "lgfx/v1/platforms/sdl/common.hpp"
#define LGFX_USE_V1
#include <LGFX_AUTODETECT.hpp>
#include <LovyanGFX.hpp>
#include "lgfx/v1/lgfx_fonts.hpp"
#include "../hal.h"
#include "../../../performance_window.hpp"


// PerformanceWindow _pw;


class HAL_Simulator : public HAL
{
    std::string type() override { return "Simulator"; }


    void init() override
    {
        // Display 
        _display = new LGFX(240, 240);
        _display->init();

        // Canvas
        _canvas = new LGFX_SpriteFx(_display);
        _canvas->createSprite(_display->width(), _display->height());

        // // Some pc window pop up slower? 
        // lgfx::delay(1500);

        // this->popFatalError("啊?");
        // this->popFatalError("原神启动失败(悲)");
    }


    void canvasUpdate() override
    {
        GetCanvas()->pushSprite(0, 0);
        // _pw.update();
    }


    void loadTextFont24() override
    {
        // https://github.com/Bodmer/TFT_eSPI/tree/master/Tools/Create_Smooth_Font/Create_font
        // http://lvgl.100ask.net/8.1/tools/fonts-zh-source.html#id7
        // https://r12a.github.io/app-conversion/
        _canvas->loadFont("../rachel/apps/assets/fonts/zpix_cn_24.vlw");
        _canvas->setTextSize(1);
    }


    void loadTextFont16() override
    {
        _canvas->setFont(&fonts::efontCN_16);
        _canvas->setTextSize(1);
    }


    void loadLauncherFont24() override
    {
        // loadTextFont24();
        _canvas->setFont(&fonts::efontCN_24);
        _canvas->setTextSize(1);
    }


    bool getButton(GAMEPAD::GamePadButton_t button) override
    {
        if (button == GAMEPAD::BTN_A)
            return !lgfx::gpio_in(36);
        else if (button == GAMEPAD::BTN_LEFT)
            return !lgfx::gpio_in(39);
        else if (button == GAMEPAD::BTN_RIGHT)
            return !lgfx::gpio_in(37);
        // else if (button == GAMEPAD::BTN_B)
        //     return !lgfx::gpio_in(38);
        // else if (button == GAMEPAD::BTN_SELECT)
        //     return !lgfx::gpio_in(38);
        // else if (button == GAMEPAD::BTN_UP)
        //     return !lgfx::gpio_in(39);
        // else if (button == GAMEPAD::BTN_DOWN)
        //     return !lgfx::gpio_in(37);
        else if (button == GAMEPAD::BTN_START)
            return !lgfx::gpio_in(38);

        return false;
    }
};
#endif
