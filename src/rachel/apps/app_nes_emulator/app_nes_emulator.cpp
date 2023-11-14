/**
 * @file app_nes_emulator.cpp
 * @author Forairaaaaa
 * @brief Ref: https://github.com/amhndu/SimpleNES
 * @version 0.1
 * @date 2023-11-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "app_nes_emulator.h"
#include "spdlog/spdlog.h"
#include "../../hal/hal.h"
#include "../assets/theme/theme.h"
#include "../utils/system/ui/ui.h"
#include "simple_nes/include/Log.h"


using namespace MOONCAKE::APPS;


void AppNes_emulator::onCreate()
{
    spdlog::info("{} onCreate", getAppName());
}


void AppNes_emulator::onResume()
{
    spdlog::info("{} onResume", getAppName());

    sn::Log::get().setLogStream(std::cout);
    sn::Log::get().setLevel(sn::Info);
    _data.emulator = new sn::Emulator;
    _data.emulator->start();
}


void AppNes_emulator::onRunning()
{
    _data.emulator->update();
}


void AppNes_emulator::onDestroy()
{
    delete _data.emulator;
    spdlog::info("{} onDestroy", getAppName());
}
