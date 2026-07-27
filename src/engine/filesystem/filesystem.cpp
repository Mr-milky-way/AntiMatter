#include "filesystem.h"
#include <fstream>


filesystem::filesystem() {
    assetsPath = GetAssetPath();
}

std::filesystem::path filesystem::GetEXdir() {
    #if defined(_WIN32)
        wchar_t buffer[MAX_PATH];
        GetModuleFileNameW(NULL, buffer, MAX_PATH);
        std::filesystem::path(buffer).parent_path();
    #elif defined(__linux__)
        char buffer[PATH_MAX];
        ssize_t length = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
        if (length != -1) {
            buffer[length] = '\0';
            return std::filesystem::path(buffer).parent_path();
        }
        return "";
    #endif
}

std::filesystem::path filesystem::GetAssetPath() {
    #if defined(_WIN32)
        wchar_t buffer[MAX_PATH];
        GetModuleFileNameW(NULL, buffer, MAX_PATH);
        std::filesystem::path(buffer).parent_path().parent_path() / "assets";
    #elif defined(__linux__)
        char buffer[PATH_MAX];
        ssize_t length = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
        if (length != -1) {
            buffer[length] = '\0';
            return std::filesystem::path(buffer).parent_path().parent_path() / "assets";
        }
        return "";
    #endif
}


std::vector<char> filesystem::GetFileBuffer(const char* filename){
    std::vector<char> out;
    if (useMatterPacks) {

    } else {
        std::ifstream file(assetsPath.string() + "/" + filename, std::ios::binary | std::ios::ate);

        if (!file) {
            std::cerr << "[filesystem::GetFileBuffer] Error: Could not open file." << std::endl;
            return {};
        }

        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        out.resize(size);

        if (file.read(out.data(), size)) {
            file.close();
            return out;
        }


        file.close();
    }
    return out;
}


bool filesystem::MountFilePack(const char* filename) {
    if (useMatterPacks){
        pakHandle.open(assetsPath.string() + "/" + filename, std::ios::binary);

        if (!pakHandle) {
            std::cerr << "[filesystem::MountFilePack] Error: Could not open file." << std::endl;
            return false;
        }
    } else {
        assetsPath = GetAssetPath().string() + "/" + filename;
    }
    return true;
}