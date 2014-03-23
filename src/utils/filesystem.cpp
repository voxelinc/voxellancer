#include "filesystem.h"

#ifdef WIN32
#include <direct.h>
#else
#include <dirent.h>
#endif

#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>


bool FileSystem::exists(const std::string& path) {
    struct stat info;
    if (stat(path.c_str(), &info) != 0) {
        return false;
    } else {
        int exists = info.st_mode & (S_IFREG | S_IFDIR);
        return exists != 0;
    }
}

bool FileSystem::createDirectory(const std::string& path) {
    return _mkdir(path.c_str()) != 0;
}

bool FileSystem::copyFile(const std::string& from, const std::string& to) {
    std::ifstream  src(from, std::ios::binary);
    if (!src.is_open()) {
        return false;
    }
    std::ofstream  dst(to, std::ios::binary);
    if (!dst.is_open()) {
        return false;
    }
    dst << src.rdbuf();
    return true;
}

std::string FileSystem::userConfigDir() {
    std::string path;
    #ifdef WIN32
    path = getenv("APPDATA");
    path += "/voxellancer/";
    #else
    path = getenv("HOME");
    path += "/.voxellancer/";
    #endif
    
    if (!exists(path)) {
        createDirectory(path);
    }
    return path;
}
