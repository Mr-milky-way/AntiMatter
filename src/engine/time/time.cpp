#include "time.h"

void EngineTimer::Update(){
    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<float> elapsed = currentTime - lastTime;
    deltaTime = elapsed.count();
    lastTime = currentTime;
    FullTime += deltaTime;
}

float EngineTimer::Delta() const {return deltaTime;}

float EngineTimer::All() const {return FullTime;}

float EngineTimer::FPS() const {return 1/deltaTime;}