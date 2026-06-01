#include "audio.h"
#include <iostream>

bool audio::initSound() {
    if (ma_engine_init(NULL, &engine) != MA_SUCCESS) {
        std::cerr << "Failed to initialize audio engine." << std::endl;
        return false;
    }

    return true;
}


audio::~audio() {
    ma_engine_stop(&engine);
}

bool audio::CreateSound(unsigned char* buffer, size_t bufferSize, Sound* outSound) {
    if (!outSound) return false;

    outSound->decoder = new ma_decoder();;

    ma_result result = ma_decoder_init_memory(buffer, bufferSize, NULL, outSound->decoder);
    if (result != MA_SUCCESS) {
        std::cerr << "Failed to initialize memory decoder." << std::endl;
        delete outSound->decoder;
        outSound->decoder = nullptr;
        return false;
    }

    result = ma_sound_init_from_data_source(
        &engine, 
        outSound->decoder, 
        0, 
        NULL, 
        &outSound->sound
    );

    if (result != MA_SUCCESS) {
        std::cerr << "Failed to bind sound to data source." << std::endl;
        ma_decoder_uninit(outSound->decoder);
        delete outSound->decoder;
        outSound->decoder = nullptr;
        return false;
    }
    
    return true;
}



void audio::PlaySound(Sound& sound){
    ma_sound_start(&sound.sound);
}



void audio::StopSound(Sound& sound){
    ma_sound_stop(&sound.sound);
    ma_sound_seek_to_pcm_frame(&sound.sound, 0);
}