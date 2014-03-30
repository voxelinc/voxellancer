#include "directoryreader.h"

#include <stdexcept>

#ifdef WIN32
#include <filesystem>
namespace std {
    namespace sys = tr2::sys;
}
#else
#include <dirent.h>
#endif

#include <glow/logging.h>



DirectoryReader::DirectoryReader():
    DirectoryReader("")
{

}

DirectoryReader::DirectoryReader(const std::string& path):
    m_path(path)
{

}

std::list<std::string> DirectoryReader::read() const {
    std::list<std::string> files;
    std::string pathBase;

    if (m_path[m_path.size() - 1] == '/') {
        pathBase = m_path;
    } else {
        pathBase = m_path + "/";
    }

#ifdef WIN32
    std::sys::path path(m_path);
    std::sys::directory_iterator end_iter;

    if (std::sys::exists(path) && std::sys::is_directory(path)) {
        for (std::sys::directory_iterator dir_iter(path); dir_iter != end_iter; ++dir_iter) {
            if (std::sys::is_regular_file(dir_iter->status())) {
                files.push_back(dir_iter->path());
            }
        }
    }
#else
    DIR* directory = opendir(pathBase.c_str());
    if (directory == nullptr) {
        glow::critical("Failed to read directory '%;'", pathBase);
        throw std::runtime_error(std::string("Directory '" + pathBase + "' not found!"));
    }

    for (struct dirent* entity = readdir(directory); entity != nullptr; entity = readdir(directory)) {
        if (entity->d_type == DT_REG) {
            files.push_back(pathBase + entity->d_name);
        }
    }

    closedir(directory);
#endif

    return files;
}

