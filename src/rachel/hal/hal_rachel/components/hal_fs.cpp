/**
 * @file hal_gamepad.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <mooncake.h>
#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>
#include "../hal_rachel.h"
#include "../hal_config.h"
#include <ArduinoJson.h>


void HAL_Rachel::_fs_init()
{
    spdlog::info("fs init");
    HAL_LOG_INFO("fs init");

    // File system 
    if (!LittleFS.begin(true)) 
    {
        spdlog::error("LittleFS init failed!");
        popFatalError("LittleFS init failed");
    }
}


static const String _system_config_path = "/_sys/cfg.json";


void HAL_Rachel::loadSystemConfig()
{
    spdlog::info("start loading config from fs");

    // Check exist
    if (!LittleFS.exists(_system_config_path))
    {
        spdlog::warn("{} not exist", _system_config_path.c_str());
        saveSystemConfig();
        return;
    }

    // Open file 
    File config_file = LittleFS.open(_system_config_path);
    if (!config_file)
        popFatalError("打开配置文件失败");

    // Parse json
    DynamicJsonDocument doc(2048);
    deserializeJson(doc, config_file);

    // Copy configs 
    _config.brightness = doc["brightness"];
    _config.volume = doc["volume"];

    spdlog::info("get config:\nbrightness: {}\nvolume: {}", _config.brightness, _config.volume);
    
    config_file.close();
}


void HAL_Rachel::saveSystemConfig()
{
    spdlog::info("start saving config to fs");

    // Open file 
    File config_file = LittleFS.open(_system_config_path, FILE_WRITE, true);
    if (!config_file)
        popFatalError("创建配置文件失败");

    // Create json 
    DynamicJsonDocument doc(2048);
    doc["brightness"] = _config.brightness;
    doc["volume"] = _config.volume;

    // Save file 
    if (serializeJson(doc, config_file) == 0)
        popFatalError("写入配置文件失败");

    config_file.close();
}


void HAL_Rachel::_system_config_init()
{
    HAL_LOG_INFO("load config from fs");
    loadSystemConfig();

    HAL_LOG_INFO("update device from config");
    updateSystemFromConfig();
}
