/**
 * @file app_music.cpp
 * @author Forairaaaaa
 * @brief Ref: https://github.com/robsoncouto/arduino-songs/tree/master
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
#include <Arduino.h>
#include <FS.h>
#include <SD.h>


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
        
        // Play 
        String music_path = _music_path;
        music_path += "/";
        music_path += music_list[selected_item].c_str();
        BuzzMusicPlayer::playFromSdCard(music_path.c_str());
    }


    destroyApp();
}


void AppMusic::onDestroy()
{
    spdlog::info("{} onDestroy", getAppName());
}
