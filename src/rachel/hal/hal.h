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
#include "lgfx_fx/lgfx_fx.h"
#else
#include <LovyanGFX.hpp>
#include "lgfx_fx/lgfx_fx.h"
#endif


namespace GAMEPAD 
{
    /**
     * @brief Game pad buttons enum 
     * 
     */
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
        GAMEPAD_BUTTON_NUM,
    };
}


namespace CONFIG
{
    /**
     * @brief System config 
     * 
     */
    struct SystemConfig_t
    {
        uint8_t brightness = 127;
        uint8_t volume = 127;
    };
}


namespace IMU
{
    /**
     * @brief IMU data 
     * 
     */
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
     * @brief Get HAL pointer, 获取HAL实例
     * 
     * @return HAL* 
     */
    static HAL* Get();

    /**
     * @brief Check if HAL is valid, 检测HAL是否有效
     * 
     * @return true 
     * @return false 
     */
    static bool Check();

    /**
     * @brief HAL injection, init() will be called here, HAL注入
     * 
     * @param hal 
     * @return true 
     * @return false 
     */
    static bool Inject(HAL* hal);

    /**
     * @brief Destroy HAL and free memory, 销毁释放HAL 
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
    LGFX_SpriteFx* _canvas;
    time_t _time_buffer;
    IMU::ImuData_t _imu_data;
    bool _is_sd_card_ready;
    CONFIG::SystemConfig_t _config;


    /**
     * @brief Getters 
     * 
     */
public:
    /**
     * @brief Display device, 获取屏幕驱动实例
     * 
     * @return LGFX_Device* 
     */
    static LGFX_Device* GetDisplay() { return Get()->_display; }

    /**
     * @brief Full screen canvas (sprite), 获取全屏Buffer实例
     * 
     * @return LGFX_SpriteFx* 
     */
    static LGFX_SpriteFx* GetCanvas() { return Get()->_canvas; }

public:
    ///
    /// System APIs
    ///

    /**
     * @brief Delay(ms), 延时(毫秒)
     * 
     * @param milliseconds 
     */
    static void Delay(unsigned long milliseconds) { Get()->delay(milliseconds); }
    virtual void delay(unsigned long milliseconds) { lgfx::delay(milliseconds); }
    
    /**
     * @brief Get the number of milliseconds passed since boot, 获取系统运行毫秒数
     * 
     * @return unsigned long 
     */
    static unsigned long Millis() { return Get()->millis(); }
    virtual unsigned long millis() { return lgfx::millis(); }

    /**
     * @brief Power off, 关机
     * 
     */
    static void PowerOff() { Get()->powerOff(); }
    virtual void powerOff() {}

    /**
     * @brief Reboot, 重启 
     * 
     */
    static void Reboot() { Get()->reboot(); }
    virtual void reboot() {}

    /**
     * @brief Set RTC time, 设置RTC时间
     * 
     * @param dateTime 
     */
    static void SetSystemTime(tm dateTime) { return Get()->setSystemTime(dateTime); }
    virtual void setSystemTime(tm dateTime) {}

    /**
     * @brief Get local time(wrap of localtime()), 获取当前时间
     * 
     * @return tm* 
     */
    static tm* GetLocalTime() { return Get()->getLocalTime(); }
    virtual tm* getLocalTime();

    /**
     * @brief Update IMU data, 刷新IMU数据
     * 
     */
    static void UpdateImuData() { Get()->updateImuData(); }
    virtual void updateImuData() {}

    /**
     * @brief Get the Imu Data, 获取IMU数据
     * 
     * @return IMU::ImuData_t& 
     */
    static IMU::ImuData_t& GetImuData() { return Get()->getImuData(); }
    IMU::ImuData_t& getImuData() { return _imu_data; }

    /**
     * @brief Buzzer beep, 蜂鸣器开始哔哔
     * 
     * @param frequency 
     * @param duration 
     */
    static void Beep(float frequency, uint32_t duration = 4294967295U) { Get()->beep(frequency, duration); }
    virtual void beep(float frequency, uint32_t duration) {}

    /**
     * @brief Stop buzzer beep, 蜂鸣器别叫了 
     * 
     */
    static void BeepStop() { Get()->beepStop(); }
    virtual void beepStop() {}
    
    /**
     * @brief Set the Beep Volume 
     * 
     * @param volume 
     */
    [[deprecated("no speaker")]]static void SetBeepVolume(uint8_t volume) { Get()->setBeepVolume(volume); }
    [[deprecated("no speaker")]]virtual void setBeepVolume(uint8_t volume) {}
    
    /**
     * @brief Check if sd card is valid, 检查SD卡是否可用
     * 
     * @return true 
     * @return false 
     */
    static bool CheckSdCard() { return Get()->checkSdCard(); }
    virtual bool checkSdCard() { return _is_sd_card_ready; }

    ///
    /// Display APIs
    ///

    /**
     * @brief Push framebuffer, 推送framebuffer到显示屏 
     * 
     */
    static void CanvasUpdate() { Get()->canvasUpdate(); }
    virtual void canvasUpdate() { GetCanvas()->pushSprite(0, 0); }

    /**
     * @brief Render fps panel, 渲染FPS面板 
     * 
     */
    static void RenderFpsPanel() { Get()->renderFpsPanel(); }
    virtual void renderFpsPanel();

    /**
     * @brief Pop error message and wait reboot, 优雅地抛个蓝屏  
     * 
     * @param msg 
     */
    static void PopFatalError(std::string msg) { Get()->popFatalError(msg); }
    virtual void popFatalError(std::string msg);
    
    ///
    /// File system APIs 
    ///

    /**
     * @brief Load 24px height text font from SD card(slower render), 从SD卡导入24px高文本字体(渲染很慢)
     * Path: /fonts/font_text_24.vlw
     * 路径: /fonts/font_text_24.vlw
     */
    static void LoadTextFont24() { Get()->loadTextFont24(); }
    virtual void loadTextFont24() {}

    /**
     * @brief Load 16px height text font from SD card(slower render), 从SD卡导入16px高文本字体(渲染很慢)
     * Path: /fonts/font_text_16.vlw
     * 路径: /fonts/font_text_16.vlw
     */
    static void LoadTextFont16() { Get()->loadTextFont16(); }
    virtual void loadTextFont16() {}

    /**
     * @brief Load 24px height launcher font from flash(fast render), 从flash导入24px高启动器用字体(渲染很快)
     * 
     */
    static void LoadLauncherFont24() { Get()->loadLauncherFont24(); }
    virtual void loadLauncherFont24() {}

    ///
    /// Gamepad APIs 
    /// 

    /**
     * @brief Get button state, 获取按键状态 
     * 
     * @param button 
     * @return true Pressing, 按下 
     * @return false Released, 松开 
     */
    static bool GetButton(GAMEPAD::GamePadButton_t button) { return Get()->getButton(button); }
    virtual bool getButton(GAMEPAD::GamePadButton_t button) { return false; }

    /**
     * @brief Get any button state, 获取任意按键状态 
     * 
     * @return true Pressing, 按下 
     * @return false Released, 松开 
     */
    static bool GetAnyButton() { return Get()->getAnyButton(); }
    virtual bool getAnyButton();

    /// 
    /// System config APIs 
    ///

    /**
     * @brief Load system config from FS, 从内部FS导入系统配置  
     * 
     */
    static void LoadSystemConfig() { Get()->loadSystemConfig(); }
    virtual void loadSystemConfig() {}

    /**
     * @brief Save system config to FS, 保存系统配置到内部FS
     * 
     */
    static void SaveSystemConfig() { Get()->saveSystemConfig(); }
    virtual void saveSystemConfig() {}

    /**
     * @brief Get the System Config, 获取系统配置 
     * 
     * @return CONFIG::SystemConfig_t& 
     */
    static CONFIG::SystemConfig_t& GetSystemConfig() { return Get()->_config; }

    /**
     * @brief Set the System Config, 设置系统配置 
     * 
     * @param cfg 
     */
    static void SetSystemConfig(CONFIG::SystemConfig_t cfg) { Get()->_config = cfg; }

    /**
     * @brief Update device to the system config, 以系统配置刷新设备
     * 
     */
    static void UpdateSystemFromConfig() { Get()->updateSystemFromConfig(); }
    virtual void updateSystemFromConfig();
};
