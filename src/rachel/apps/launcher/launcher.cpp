/**
 * @file launcher.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "launcher.h"
#include "lgfx/v1/lgfx_fonts.hpp"
#include "spdlog/spdlog.h"
#include "../../hal/hal.h"
#include <LovyanGFX.hpp>
#include "../assets/theme/theme.h"
#include "../assets/icons/icons.h"
#include "assets/launcher_bottom_panel.h"


using namespace MOONCAKE::APPS;


void Launcher::onCreate()
{
    spdlog::info("{} onCreate", getAppName());

    // Enable bg running 
    setAllowBgRunning(true);
    // Auto start 
    startApp();

    _create_menu();
}


void Launcher::onResume()
{
    spdlog::info("{} onResume", getAppName());

    // Load resources 
    HAL::LoadLauncherFont24();
    // HAL::LoadTextFont24();
    HAL::GetCanvas()->setTextScroll(false);

    _update_clock(true);
}


void Launcher::onRunning()
{
    _update_clock();
    _update_menu();
}


void Launcher::onRunningBG()
{
    // If only launcher running still 
    if (mcAppGetFramework()->getAppManager().getCreatedAppNum() == 1)
    {
        spdlog::info("back to launcher");
        
        // Back to business
        mcAppGetFramework()->startApp(this);

        // Play app close anim 
        HAL::LoadLauncherFont24();
        _update_clock(true);
        _play_app_anim(false);
    }
}


void Launcher::onPause()
{
    // Play app open anim 
    _play_app_anim(true);
}


void Launcher::onDestroy()
{
    spdlog::info("{} onDestroy", getAppName());

    _destroy_menu();
}


void Launcher::_update_clock(bool updateNow)
{
    if ((HAL::Millis() - _data.clock_update_count) > _data.clock_update_interval || updateNow)
    {
        // Update clock  
        strftime(_data.string_buffer, 10, "%H:%M", HAL::GetLocalTime());
        _data.clock = _data.string_buffer;
        
        _data.clock_update_count = HAL::Millis();
    }
}

