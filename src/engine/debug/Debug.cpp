#include "Debug.h"
#include "../filesystem/filesystem.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <chrono> 
#include <thread>
#include <mutex>
#include <queue>

debug::debug() {
    LogLevel = ALL;

    std::filesystem::path logDir = filesystem::GetEXdir().parent_path() / "logs";
    std::filesystem::create_directory(logDir);
    std::string filename = std::to_string(std::time(nullptr)) + ".log";
    std::filesystem::path logFilePath = logDir / filename;\
    LogFile.open(logFilePath, std::ios::binary);
    if (!LogFile){
        std::cout << TextColor::red << "NO LOG FILE AT" << TextColor::reset << logFilePath << std::endl;
    }
    #if defined(__linux__)
    LogFile << "use cat " << logFilePath << " To open this file with color" << "\n";
    #elif defined(_WIN32)
    LogFile << "use Get-Content " << logFilePath << " To open this file with color" << "\n";
    #endif
    LogFile.flush();

    workerThread = std::thread(&debug::LogQueue, this);
}

debug::~debug() {  
    {
        std::unique_lock<std::mutex> lock(queueMtx);
        stopThread = true;
    }
    if (workerThread.joinable()) {
        workerThread.join();
    }
    if (LogFile.is_open()) {
        LogFile.close();
    }
}


void debug::LogQueue() {
    while (true){
        {
            std::unique_lock<std::mutex> lock(queueMtx);
            while (!logQueue.empty()) {
                std::cout << logQueue.front() << "\n";
                LogFile << logQueue.front() << "\n";
                logQueue.pop();
            }
        }
        LogFile.flush();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(2500));
        
        std::unique_lock<std::mutex> lock(queueMtx);
        if(stopThread && logQueue.empty()) break;
    }
}

void debug::Log(std::string text) {
    if (LogLevel == ALL) {
        std::unique_lock<std::mutex> lock(queueMtx);
        logQueue.push(text);
    }
}

void debug::Error(std::string text) {
    if (LogLevel == ALL || LogLevel == ERROR_ONLY) {
        std::unique_lock<std::mutex> lock(queueMtx);
        logQueue.push(TextColor::red + text + TextColor::reset);
    }
}