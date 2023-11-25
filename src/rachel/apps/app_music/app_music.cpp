/**
 * @file app_music.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "app_music.h"
#include "spdlog/spdlog.h"
#include "../../hal/hal.h"
#include "../assets/theme/theme.h"
#include "../utils/system/ui/ui.h"
#include "../utils/system/audio/audio.h"
#ifdef ESP_PLATFORM
#include <Arduino.h>
#include <FS.h>
#include <SD.h>
#endif


using namespace MOONCAKE::APPS;
using namespace SYSTEM::UI;
using namespace SYSTEM::AUDIO;


void AppMusic::onCreate()
{
    spdlog::info("{} onCreate", getAppName());
}


void AppMusic::onResume()
{
    spdlog::info("{} onResume", getAppName());
}


#ifdef ESP_PLATFORM
static const String _music_path = "/buzz_music";

void AppMusic::onRunning()
{
    if (!HAL::CheckSdCard())
        HAL::PopFatalError("没SD卡啊朋友");
    spdlog::info("try loading music from SD card in {}", _music_path.c_str());


    // Check path 
    if (!SD.exists(_music_path))
    {
        std::string msg = "音乐路径不存在\n  (";
        msg += _music_path.c_str();
        msg += ")";
        HAL::PopFatalError(msg);
    }


    // List music dir 
    auto music_directory = SD.open(_music_path);
    std::vector<std::string> music_list = {"[MUSIC]"};
    while (1)
    {
        File entry =  music_directory.openNextFile();

        if (!entry)
            break;

        if (!entry.isDirectory())
        {
            // Filter 
            if (std::strstr(entry.name(), ".json") != NULL)
            {
                music_list.push_back(entry.name());
                spdlog::info("get file: {} size: {}", entry.name(), entry.size());
            }
        }
        
        entry.close();    
    }
    if (music_list.size() == 1)
        HAL::PopFatalError("没音乐啊朋友");
    music_list.push_back("Quit");


    // Create select menu
    SelectMenu menu;
    while (1)
    {
        auto selected_item = menu.waitResult(music_list);

        if (selected_item == music_list.size() - 1)
            break;

        // ~ 
        HAL::GetCanvas()->fillSmoothRoundRect((240 - 180) / 2,  (240 - 120) / 2, 180, 120, 20, THEME_COLOR_LIGHT);
        HAL::GetCanvas()->setTextColor(THEME_COLOR_DARK, THEME_COLOR_LIGHT);
        HAL::GetCanvas()->drawCenterString("Playing..", 120, 120 - 12);
        HAL::CanvasUpdate();
        
        // Play 
        String music_path = _music_path;
        music_path += "/";
        music_path += music_list[selected_item].c_str();
        BuzzMusicPlayer::playFromSdCard(music_path.c_str());
    }


    destroyApp();
}
#else

void AppMusic::onRunning()
{
    HAL::PopFatalError("懒得抽象了");
}

#endif


void AppMusic::onDestroy()
{
    spdlog::info("{} onDestroy", getAppName());
}
