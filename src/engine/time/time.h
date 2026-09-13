#pragma once
#include <chrono>

class EngineTimer {
public:
    void Update();
    float Delta() const;
    float All() const;
    float FPS() const;
private:
    float deltaTime = 0;
    float FullTime = 0;
    std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();
};