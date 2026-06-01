#include "miniaudio/miniaudio.h"

#pragma once
struct Sound {
    ma_sound sound;
    ma_decoder* decoder = nullptr; // Retained for memory-streaming playback
};
class audio {
private:
    ma_engine engine;
public:
    ~audio();
    bool initSound();


    bool CreateSound(unsigned char* buffer, size_t bufferSize, Sound* outSound);
};