/**
 * @file buzz_music_player.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <mooncake.h>
#include "buzz_music_player.h"
#include "../../../hal/hal.h"
#ifdef ESP_PLATFORM
#include <Arduino.h>
#include <SD.h>
#include <ArduinoJson.h>
#endif


using namespace SYSTEM::AUDIO;


#ifdef ESP_PLATFORM
void BuzzMusicPlayer::playRaw(BuzzMusic_t* buzzMusic)
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


void BuzzMusicPlayer::playFromSdCard(const char* buzzMusicPath)
{
    // Try open
    spdlog::info("try open {}", buzzMusicPath);
    auto music_file = SD.open(buzzMusicPath, FILE_READ);
    if (!music_file)
        HAL::PopFatalError("文件打开失败\n " + std::string(buzzMusicPath));

    int melody_tempo = 0;
    size_t melody_size = 0;
    BuzzMusic_t* buzz_music = nullptr;

    // Parse json
    {
        DynamicJsonDocument doc(2048);
        deserializeJson(doc, music_file);

        melody_tempo = doc["tempo"];
        melody_size = doc["melody"].size();
        spdlog::info("melody tempo: {} size: {}", melody_tempo, melody_size);

        buzz_music = new BuzzMusic_t(melody_tempo, melody_size);
        for (int i = 0; i < doc["melody"].size(); i++)
            buzz_music->melody[i] = doc["melody"][i];

        music_file.close();
    }

    // Play 
    playRaw(buzz_music);
    
    delete buzz_music;
}
#else

void playRaw(BuzzMusic_t* buzzMusic) {}
void playFromSdCard(const char* buzzMusicPath) {}

#endif
