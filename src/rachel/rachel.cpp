/**
 * @file rachel.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "rachel.h"
#include <mooncake.h>
#include "hal/hal.h"
#ifndef ESP_PLATFORM
#include "hal/hal_simulator/hal_simulator.hpp"
#else
#include "hal/hal_rachel/hal_rachel.h"
#endif
#include "apps/apps.h"


using namespace MOONCAKE;
static Mooncake* _mooncake = nullptr;


void RACHEL::Setup()
{
    spdlog::info("Rachel Setup");

    // HAL injection 
    #ifndef ESP_PLATFORM
    HAL::Inject(new HAL_Simulator);
    #else
    HAL::Inject(new HAL_Rachel);
    #endif

    // Mooncake framework 
    _mooncake = new Mooncake;
    _mooncake->init();

    // Install launcher 
    auto launcher = new APPS::Launcher_Packer;
    _mooncake->installApp(launcher);

    // Install apps 
    rachel_app_install_callback(_mooncake);

    // Create launcher 
    _mooncake->createApp(launcher);
}


void RACHEL::Loop()
{
    _mooncake->update();
}


void RACHEL::Destroy()
{
    // Free 
    delete _mooncake;
    HAL::Destroy();
    spdlog::warn("Rachel destroy");
}

