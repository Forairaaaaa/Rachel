/**
 * @file hal.h
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
#define LGFX_USE_V1
#include <LGFX_AUTODETECT.hpp>
#include <LovyanGFX.hpp>
#include "lgfx/v1/LGFXBase.hpp"
#include "lgfx/v1/LGFX_Sprite.hpp"
#include "lgfx/v1_autodetect/LGFX_AutoDetect_sdl.hpp"
#include <cstdint>
#include <iostream>
#include <string>
#else
#include <LovyanGFX.hpp>
#endif


/**
 * @brief Game pad button enum 
 * 
 */
namespace GAMEPAD 
{
    enum GamePadButton_t
    {
        BTN_START = 0,
        BTN_SELECT,
        BTN_UP,
        BTN_LEFT,
        BTN_RIGHT,
        BTN_DOWN,
        BTN_X,
        BTN_Y,
        BTN_A,
        BTN_B,
        BTN_LEFT_STICK,
    };
}


/**
 * @brief IMU data 
 * 
 */
namespace IMU
{
    struct ImuData_t
    {
        float accelX;
        float accelY;
        float accelZ;
    };
}


/**
 * @brief Singleton like pattern to simplify hal's getter 
 * 1) Inherit and override methods to create a specific hal 
 * 2) Use HAL::Inject() to inject your hal
 * 3) Use HAL:Get() to get this hal wherever you want 
 */
class HAL 
{
private:
    static HAL* _hal;

public:
    /**
     * @brief Get HAL pointer 
     * 
     * @return HAL* 
     */
    static HAL* Get();

    /**
     * @brief Check if HAL is valid 
     * 
     * @return true 
     * @return false 
     */
    static bool Check();

    /**
     * @brief HAL injection, init() will be called here  
     * 
     * @param hal 
     * @return true 
     * @return false 
     */
    static bool Inject(HAL* hal);

    /**
     * @brief Destroy HAL and free memory 
     * 
     */
    static void Destroy();

    

    /**
     * @brief Base class 
     * 
     */
public:
    HAL() :
        _display(nullptr),
        _canvas(nullptr),
        _is_sd_card_ready(false)
        {}
    virtual ~HAL() {}
    virtual std::string type() { return "Base"; }
    virtual void init() {}
    
    /**
     * @brief Components 
     * 
     */
protected:
    LGFX_Device* _display;
    LGFX_Sprite* _canvas;
    time_t _time_buffer;
    IMU::ImuData_t _imu_data;
    bool _is_sd_card_ready;


    /**
     * @brief Getters 
     * 
     */
public:
    /**
     * @brief Display device 
     * 
     * @return LGFX_Device* 
     */
    static LGFX_Device* GetDisplay() { return Get()->_display; }

    /**
     * @brief Full screen canvas (sprite)
     * 
     * @return LGFX_Sprite* 
     */
    static LGFX_Sprite* GetCanvas() { return Get()->_canvas; }

public:
    /**
     * @brief System APIs
     * 
     */
    static void Delay(unsigned long milliseconds) { Get()->delay(milliseconds); }
    virtual void delay(unsigned long milliseconds) { lgfx::delay(milliseconds); }
    
    static unsigned long Millis() { return Get()->millis(); }
    virtual unsigned long millis() { return lgfx::millis(); }

    static void PowerOff() { Get()->powerOff(); }
    virtual void powerOff() {}

    static void Reboot() { Get()->reboot(); }
    virtual void reboot() {}

    static void SetSystemTime(tm dateTime) { return Get()->setSystemTime(dateTime); }
    virtual void setSystemTime(tm dateTime) {}

    static tm* GetLocalTime() { return Get()->getLocalTime(); }
    virtual tm* getLocalTime();

    static void UpdateImuData() { Get()->updateImuData(); }
    virtual void updateImuData() {}

    static IMU::ImuData_t& GetImuData() { return Get()->getImuData(); }
    IMU::ImuData_t& getImuData() { return _imu_data; }

    static void Beep(float frequency, uint32_t duration = 4294967295U) { Get()->beep(frequency, duration); }
    virtual void beep(float frequency, uint32_t duration) {}

    static void BeepStop() { Get()->beepStop(); }
    virtual void beepStop() {}

    static void SetBeepVolume(uint8_t volume) { Get()->setBeepVolume(volume); }
    virtual void setBeepVolume(uint8_t volume) {}

    static bool CheckSdCard() { return Get()->checkSdCard(); }
    virtual bool checkSdCard() { return _is_sd_card_ready; }


    /**
     * @brief Display APIs 
     * 
     */
    // Push frame buffer 
    static void CanvasUpdate() { Get()->canvasUpdate(); }
    virtual void canvasUpdate() { GetCanvas()->pushSprite(0, 0); }

    static void RenderFpsPanel() { Get()->renderFpsPanel(); }
    virtual void renderFpsPanel();

    // Pop error message and wait reboot or power off 
    static void PopFatalError(std::string msg) { Get()->popFatalError(msg); }
    virtual void popFatalError(std::string msg);
    

    /**
     * @brief File system APIs 
     * 
     */
    static void LoadTextFont24() { Get()->loadTextFont24(); }
    virtual void loadTextFont24() {}

    static void LoadTextFont16() { Get()->loadTextFont16(); }
    virtual void loadTextFont16() {}

    static void LoadLauncherFont24() { Get()->loadLauncherFont24(); }
    virtual void loadLauncherFont24() {}


    /**
     * @brief Gamepad APIs 
     * 
     */
    // Get button state, @true: Pressing @false: Released 
    static bool GetButton(GAMEPAD::GamePadButton_t button) { return Get()->getButton(button); }
    virtual bool getButton(GAMEPAD::GamePadButton_t button) { return false; }

    static bool GetAnyButton() { return Get()->getAnyButton(); }
    virtual bool getAnyButton();
};
