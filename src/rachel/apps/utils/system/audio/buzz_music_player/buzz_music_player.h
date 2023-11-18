/**
 * @file buzz_music_player.h
 * @author Forairaaaaa
 * @brief Ref: https://github.com/robsoncouto/arduino-songs
 * @version 0.1
 * @date 2023-11-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <iostream>
#include <string>


namespace SYSTEM::AUDIO
{
    struct BuzzMusic_t
    {
        int tempo = 0;
        std::size_t melodySize = 0; 
        int* melody = nullptr;

        BuzzMusic_t(int tempo, std::size_t melodySize)
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

    class BuzzMusicPlayer
    {
    public:
        static void playRaw(BuzzMusic_t* buzzMusic);
        static void playFromSdCard(const char* buzzMusicPath);
    };
}
