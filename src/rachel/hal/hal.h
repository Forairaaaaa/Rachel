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
#include <LovyanGFX.hpp>
#ifndef ESP_PLATFORM
#include "lgfx/v1/LGFXBase.hpp"
#include "lgfx/v1/LGFX_Sprite.hpp"
#include "lgfx/v1_autodetect/LGFX_AutoDetect_sdl.hpp"
#include <cstdint>
#include <iostream>
#include <string>
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
        _display(nullptr)
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


    /**
     * @brief Display APIs 
     * 
     */
    // Push frame buffer 
    static void CanvasUpdate() { Get()->canvasUpdate(); }
    virtual void canvasUpdate() { GetCanvas()->pushSprite(0, 0); }

    static void RenderFpsPanel() { Get()->renderFpsPanel(); }
    virtual void renderFpsPanel();

    // Pop error message and wait reboot 
    static void PopFatalError(std::string& msg) { Get()->popFatalError(msg); }
    virtual void popFatalError(std::string& msg) {}
    

    /**
     * @brief File system APIs 
     * 
     */
    static void LoadSystemFont24() { Get()->loadSystemFont24(); }
    virtual void loadSystemFont24() {}


    /**
     * @brief Gamepad APIs 
     * 
     */
    // Get button state, @true: Pressing @false: Released 
    static bool GetButton(GAMEPAD::GamePadButton_t button) { return Get()->getButton(button); }
    virtual bool getButton(GAMEPAD::GamePadButton_t button) { return false; }
};
