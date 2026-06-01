#include <string>
#include <queue>
#include <iostream>
#include <cstdint>
#include <thread>
#include <mutex>
#include "../filesystem/filesystem.h"

#pragma once

enum e_logLevel : uint8_t {
    NONE,
    ERROR_ONLY,
    ALL
};

namespace TextColor {
    const std::string reset   = "\033[0m";
    const std::string bold    = "\033[1m";
    const std::string red     = "\033[31m";
    const std::string green   = "\033[32m";
    const std::string yellow  = "\033[33m";
    const std::string cyan    = "\033[36m";
};
class debug {
private:
    bool stopThread = false;
    std::mutex queueMtx;
    void LogQueue();
    std::thread workerThread;

    std::queue<std::string> logQueue;
    std::ofstream LogFile;
public:

    debug();
    ~debug();
    e_logLevel LogLevel;

    void Log(std::string text);
    void Error(std::string text);
};