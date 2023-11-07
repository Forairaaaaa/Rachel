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


#define LCD_MOSI_PIN 40
#define LCD_MISO_PIN -1
#define LCD_SCLK_PIN 41
#define LCD_DC_PIN   42
#define LCD_CS_PIN   44
#define LCD_RST_PIN  12
#define LCD_BUSY_PIN -1
#define LCD_BL_PIN   11


class LGFX_Rachel : public lgfx::LGFX_Device 
{
    lgfx::Panel_ST7789 _panel_instance;
    lgfx::Bus_SPI _bus_instance;
    lgfx::Light_PWM _light_instance;

public:
    LGFX_Rachel(void) {
        {
            auto cfg = _bus_instance.config();

            cfg.pin_mosi   = LCD_MOSI_PIN;
            cfg.pin_miso   = LCD_MISO_PIN;
            cfg.pin_sclk   = LCD_SCLK_PIN;
            cfg.pin_dc     = LCD_DC_PIN;
            cfg.freq_write = 80000000;

            _bus_instance.config(cfg);
            _panel_instance.setBus(&_bus_instance);
        }
        {
            auto cfg = _panel_instance.config();

            cfg.invert       = true;
            cfg.pin_cs       = LCD_CS_PIN;
            cfg.pin_rst      = LCD_RST_PIN;
            cfg.pin_busy     = LCD_BUSY_PIN;
            cfg.panel_width  = 240;
            cfg.panel_height = 240;
            cfg.offset_x     = 0;
            cfg.offset_y     = 0;

            _panel_instance.config(cfg);
        }
        {
            auto cfg = _light_instance.config();

            cfg.pin_bl = LCD_BL_PIN;
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
}
