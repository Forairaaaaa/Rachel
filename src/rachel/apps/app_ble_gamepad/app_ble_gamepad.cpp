/**
 * @file app_ble_controller.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "app_ble_gamepad.h"
#include "spdlog/spdlog.h"
#include "../../hal/hal.h"
#include "../assets/theme/theme.h"
#ifdef ESP_PLATFORM
#include <BleGamepad.h>
#endif


using namespace MOONCAKE::APPS;


void AppBle_gamepad::onCreate()
{
    spdlog::info("{} onCreate", getAppName());
}


void AppBle_gamepad::onResume()
{
    spdlog::info("{} onResume", getAppName());
}


void AppBle_gamepad::onRunning()
{
#ifdef ESP_PLATFORM
    HAL::LoadTextFont24();
    HAL::GetCanvas()->fillScreen(THEME_COLOR_DARK);
    HAL::GetCanvas()->setTextColor(THEME_COLOR_LIGHT, THEME_COLOR_DARK);
    HAL::GetCanvas()->drawCenterString("已开启BLE手柄", 120, 120 - 48);
    HAL::GetCanvas()->drawCenterString("Rachel BLE Gamepad", 122, 120 - 12);
    HAL::CanvasUpdate();

    // Ram is limit.. 
    HAL::GetCanvas()->deleteSprite();


    auto ble_gamepad = new BleGamepad("Rachel BLE Gamepad");
    BleGamepadConfiguration bleGamepadConfig;
    bleGamepadConfig.setAutoReport(false);
    ble_gamepad->begin(&bleGamepadConfig);


    uint16_t lx = 0;
    uint16_t ly = 0;
    while (1)
    {
        HAL::Delay(20);

        if (ble_gamepad->isConnected())
        {
            lx = 16384;
            ly = 16384;
            if (HAL::GetButton(GAMEPAD::BTN_UP))
                ly = 0;
            else if (HAL::GetButton(GAMEPAD::BTN_DOWN))
                ly = 32767;
            else if (HAL::GetButton(GAMEPAD::BTN_LEFT))
                lx = 0;
            else if (HAL::GetButton(GAMEPAD::BTN_RIGHT))
                lx = 32767;
            ble_gamepad->setX(lx);
            ble_gamepad->setY(ly);


            if (HAL::GetButton(GAMEPAD::BTN_Y))
                ble_gamepad->press(BUTTON_1);
            else
                ble_gamepad->release(BUTTON_1);

            if (HAL::GetButton(GAMEPAD::BTN_X))
                ble_gamepad->press(BUTTON_2);
            else
                ble_gamepad->release(BUTTON_2);

            if (HAL::GetButton(GAMEPAD::BTN_A))
                ble_gamepad->press(BUTTON_3);
            else
                ble_gamepad->release(BUTTON_3);

            if (HAL::GetButton(GAMEPAD::BTN_B))
                ble_gamepad->press(BUTTON_4);
            else
                ble_gamepad->release(BUTTON_4);

            if (HAL::GetButton(GAMEPAD::BTN_START))
                ble_gamepad->press(BUTTON_5);
            else
                ble_gamepad->release(BUTTON_5);

            if (HAL::GetButton(GAMEPAD::BTN_SELECT))
                ble_gamepad->press(BUTTON_6);
            else
                ble_gamepad->release(BUTTON_6);
            
            ble_gamepad->sendReport();
        }

        if (HAL::GetButton(GAMEPAD::BTN_LEFT_STICK))
        {
            // Long press quit 
            int count = 0;
            while (HAL::GetButton(GAMEPAD::BTN_LEFT_STICK))
            {
                HAL::Delay(50);
                count++;
                if (count > 1000 / 50)
                {
                    HAL::Reboot();
                    // break;
                }
            }
        }
    }

    delete ble_gamepad;
    HAL::GetCanvas()->createSprite(HAL::GetDisplay()->width(), HAL::GetDisplay()->height());
    destroyApp();
#else
    HAL::PopFatalError("懒得抽象了");
#endif
}


void AppBle_gamepad::onDestroy()
{
    spdlog::info("{} onDestroy", getAppName());
}
