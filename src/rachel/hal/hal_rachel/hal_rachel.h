/**
 * @file hal_rachel.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../hal.h"


class HAL_Rachel : public HAL
{
private:
    void _power_init();
    void _disp_init();
    void _fs_init();
    void _gamepad_init();
    std::array<uint8_t, 11> _gamepad_key_map;

public:
    std::string type() override { return "Rachel"; }
    void init() override;
    inline void canvasUpdate() override { GetCanvas()->pushSprite(0, 0); }
    inline void delay(unsigned long milliseconds) override { lgfx::delay(milliseconds); }
    inline unsigned long millis() override { return lgfx::millis(); }
    void loadSystemFont24() override;
    bool getButton(GAMEPAD::GamePadButton_t button) override;
    void powerOff() override;
};
