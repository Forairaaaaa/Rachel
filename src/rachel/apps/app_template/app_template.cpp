/**
 * @file app_template.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "app_template.h"
#include "spdlog/spdlog.h"
#include "../../hal/hal.h"
#include "../assets/theme/theme.h"


using namespace MOONCAKE::APPS;


// Like setup()...
void AppTemplate::onResume()
{
    spdlog::info("{} onResume", getAppName());
}


// Like loop()...
void AppTemplate::onRunning()
{    
    spdlog::info("咩啊");
    HAL::Delay(1000);

    _data.count++;
    if (_data.count > 5)
        destroyApp();
}


void AppTemplate::onDestroy()
{
    spdlog::info("{} onDestroy", getAppName());
}
