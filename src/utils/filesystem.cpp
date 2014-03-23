#include "filesystem.h"

#ifdef WIN32
#include <filesystem>
namespace std {
    namespace sys = tr2::sys;
}
#else
#include <dirent.h>
#include <unistd.h>
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
        int exists = info.st_mode & (S_IFREG | S_IFDIR); // is file or directory
        return exists != 0;
    }
}

bool FileSystem::removeFile(const std::string& path) {
    return ::remove(path.c_str()) == 0;
}

bool FileSystem::createDirectory(const std::string& path) {
#ifdef WIN32
    return std::sys::create_directory(std::sys::path(path));
#else
    return mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0;
#endif
}

bool FileSystem::removeDirectory(const std::string& path) {
#ifdef WIN32 
    return std::sys::remove_directory(std::sys::path(path));
#else
    return rmdir(path.c_str()) == 0;
#endif
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
    path += "/voxellancer";
#else
    path = getenv("HOME");
    path += "/.voxellancer";
#endif
    
    if (!exists(path)) {
        createDirectory(path);
    }
    return path;
}
