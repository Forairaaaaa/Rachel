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
#include <Arduino.h>
#include <SD.h>
#include <ArduinoJson.h>


using namespace MOONCAKE::APPS;
using namespace SYSTEM::UI;


struct BuzzMusic_t
{
    int tempo = 180;
    size_t melodySize = 0; 
    int* melody = nullptr;

    BuzzMusic_t(int tempo, size_t melodySize)
    {
        this->tempo = tempo;
        this->melodySize = melodySize;
        melody = new int[this->melodySize];
    }

    ~BuzzMusic_t()
    {
        delete[] this->melody;
    }
};
void _load_json_buzz_music();
void _parse_json_buzz_music(File& musicFile);
void _play_buzz_muisc(BuzzMusic_t* buzzMusic);


void AppMusic::onCreate()
{
    spdlog::info("{} onCreate", getAppName());
}


void AppMusic::onResume()
{
    spdlog::info("{} onResume", getAppName());
}


void AppMusic::onRunning()
{
    _load_json_buzz_music();
}


static const String _music_path = "/buzz_music";

void _load_json_buzz_music()
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
            music_list.push_back(entry.name());
            spdlog::info("get file: {} size: {}", entry.name(), entry.size());
        }
        
        entry.close();    
    }
    if (music_list.size() == 1)
        HAL::PopFatalError("没音乐啊朋友");


    // Create select menu
    SelectMenu menu;
    auto selected_item = menu.waitResult(music_list);


    // Try open 
    String music_path = _music_path;
    music_path += "/";
    music_path += music_list[selected_item].c_str();
    spdlog::info("try open {}", music_path.c_str());
    auto music_file = SD.open(music_path, FILE_READ);


    _parse_json_buzz_music(music_file);
}


void _parse_json_buzz_music(File& musicFile)
{
    int melody_tempo = 0;
    size_t melody_size = 0;
    BuzzMusic_t* buzz_music = nullptr;

    // Parse json
    {
        DynamicJsonDocument doc(2048);
        deserializeJson(doc, musicFile);

        melody_tempo = doc["tempo"];
        melody_size = doc["melody"].size();
        spdlog::info("melody tempo: {} size: {}", melody_tempo, melody_size);

        buzz_music = new BuzzMusic_t(melody_tempo, melody_size);
        for (int i = 0; i < doc["melody"].size(); i++)
            buzz_music->melody[i] = doc["melody"][i];
    }

    // Play 
    _play_buzz_muisc(buzz_music);

    musicFile.close();
    delete buzz_music;
}


void _play_buzz_muisc(BuzzMusic_t* buzzMusic)
{
    // sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
    // there are two values per note (pitch and duration), so for each note there are four bytes
    int notes = buzzMusic->melodySize / 2;

    // this calculates the duration of a whole note in ms
    int wholenote = (60000 * 4) / buzzMusic->tempo;

    int divider = 0, noteDuration = 0;

    // iterate over the notes of the melody.
    // Remember, the array is twice the number of notes (notes + durations)
    for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) 
    {
        // calculates the duration of each note
        divider = buzzMusic->melody[thisNote + 1];

        if (divider > 0) 
        {
            // regular note, just proceed
            noteDuration = (wholenote) / divider;
        } 
        else if (divider < 0) 
        {
            // dotted notes are represented with negative durations!!
            noteDuration = (wholenote) / abs(divider);
            noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // we only play the note for 90% of the duration, leaving 10% as a pause
        // tone(buzzer, melody[thisNote], noteDuration * 0.9);
        HAL::Beep(buzzMusic->melody[thisNote], noteDuration * 0.9);

        // Wait for the specief duration before playing the next note.
        // delay(noteDuration);
        HAL::Delay(noteDuration);

        // stop the waveform generation before the next note.
        // noTone(buzzer);
        HAL::BeepStop();
    }
}


void AppMusic::onDestroy()
{
    spdlog::info("{} onDestroy", getAppName());
}
