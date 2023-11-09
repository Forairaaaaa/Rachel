/**
 * @file hal_gamepad.cpp
 * @author Forairaaaaa
 * @brief Ref: https://github.com/lovyan03/LovyanGFX/blob/master/examples/HowToUse/2_user_setting/2_user_setting.ino
 * @version 0.1
 * @date 2023-11-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <mooncake.h>
#include "../hal_rachel.h"
#include <Arduino.h>
#include "../hal_config.h"


class LGFX_Rachel : public lgfx::LGFX_Device 
{
    lgfx::Panel_ST7789 _panel_instance;
    lgfx::Bus_SPI _bus_instance;
    lgfx::Light_PWM _light_instance;

public:
    LGFX_Rachel(void) {
        {
            auto cfg = _bus_instance.config();

            cfg.pin_mosi   = HAL_PIN_LCD_MOSI;
            cfg.pin_miso   = HAL_PIN_SD_MISO;
            cfg.pin_sclk   = HAL_PIN_LCD_SCLK;
            cfg.pin_dc     = HAL_PIN_LCD_DC;
            cfg.freq_write = 80000000;
            cfg.spi_3wire  = false;

            _bus_instance.config(cfg);
            _panel_instance.setBus(&_bus_instance);
        }
        {
            auto cfg = _panel_instance.config();

            cfg.invert       = true;
            cfg.pin_cs       = HAL_PIN_LCD_CS;
            cfg.pin_rst      = HAL_PIN_LCD_RST;
            cfg.pin_busy     = HAL_PIN_LCD_BUSY;
            cfg.panel_width  = 240;
            cfg.panel_height = 240;
            cfg.offset_x     = 0;
            cfg.offset_y     = 0;
            cfg.bus_shared   = true;

            _panel_instance.config(cfg);
        }
        {
            auto cfg = _light_instance.config();

            cfg.pin_bl = HAL_PIN_LCD_BL;
            cfg.invert = false;
            cfg.freq   = 44100;
            cfg.pwm_channel = 7;

            _light_instance.config(cfg);
            _panel_instance.setLight(&_light_instance);
        }
            
        setPanel(&_panel_instance);
    }
};


void HAL_Rachel::_disp_init()
{
    spdlog::info("display init");

    _display = new LGFX_Rachel;
    _display->init();

    _canvas = new LGFX_Sprite(_display);
    _canvas->createSprite(_display->width(), _display->height());
    
    HAL_LOGGER_INIT();
    _disp_logo();
    HAL_LOG_INFO("rachel init");
}


static const std::string _logo = R"(
    ____  ___   ________  __________
   / __ \/   | / ____/ / / / ____/ /
  / /_/ / /| |/ /   / /_/ / __/ / /
 / _, _/ ___ / /___/ __  / /___/ /___
/_/ |_/_/  |_\____/_/ /_/_____/_____/
)";

void HAL_Rachel::_disp_logo()
{
    _canvas->setFont(&fonts::Font0);
    _canvas->setTextColor(TFT_ORANGE, TFT_BLACK);

    for (int i = 0; i < _logo.size(); i++)
    {
        _canvas->printf("%c", _logo[i]);
        if (i % 20 == 0)
            _canvas->pushSprite(0, 0);
    }
    _canvas->printf("\n- @author Forairaaaaa\n");
    _canvas->printf("\n- @build at %s %s\n\n", __TIME__, __DATE__);
    _canvas->pushSprite(0, 0);
}


void HAL_Rachel::_sum_up()
{
    // Pause if btn A is pressing 
    if (getButton(GAMEPAD::BTN_A))
    {
        HAL_LOG_WARN("btn A pressed and pause");
        HAL_LOG_WARN("press btn start to proceed");
        while (1)
        {
            delay(100);
            if (getButton(GAMEPAD::BTN_START))
                break;
        }
    }

    HAL_LOG_INFO("hal init success!");
    HAL_LOG_INFO("starting mooncake");
    HAL_LOG_INFO("bye");
}

