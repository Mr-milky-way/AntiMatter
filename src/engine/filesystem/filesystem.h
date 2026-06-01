#include <cstdint>
#include <filesystem>
#include <fstream> 
#include <iostream>
#include <vector>

#if defined(_WIN32)
#include <windows.h>
#elif defined(__linux__)
#include <unistd.h>
#include <limits.h>
#endif

#pragma once

#pragma pack(push, 1)
struct fileHeader {
    char hash[256];
    uint32_t fileoffset;
    uint32_t fileLen;
};

struct MatterPackHeader {
    char signature[8]; //should be aNTImATR
    uint16_t version; //0
    uint32_t NumberOfFiles;
    fileHeader files[];
};
#pragma pack(pop)


class filesystem {
private:
    std::filesystem::path GetAssetPath();
    std::filesystem::path assetsPath;

    std::ifstream pakHandle;
public:

    static std::filesystem::path GetEXdir();
    filesystem();
    bool useMatterPacks = false;

    std::vector<char> GetFileBuffer(const char* filename);

    bool MountFilePack(const char* filename);
};