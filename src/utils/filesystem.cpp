#include "filesystem.h"

#include <stdlib.h>

#include <glow/logging.h>

#include "def_filesystem.h"

bool FileSystem::exists(const std::string& path) {
    return filesystem::exists(filesystem::path(path));
}

bool FileSystem::removeFile(const std::string& path) {
    return filesystem::remove(filesystem::path(path));
}

bool FileSystem::createDirectory(const std::string& path) {
    return filesystem::create_directory(filesystem::path(path));
}

bool FileSystem::removeDirectory(const std::string& path) {
#ifdef WIN32
    return filesystem::remove_directory(filesystem::path(path));
#else
    return filesystem::remove(filesystem::path(path));
#endif
}

bool FileSystem::copyFile(const std::string& from, const std::string& to) {
    try {
        filesystem::copy_file(filesystem::path(from), filesystem::path(to), filesystem::copy_option::fail_if_exists);
    } catch (const filesystem::filesystem_error& e) {
        glow::warning("filesystem: %;", e.what());
        return false;
    }
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
