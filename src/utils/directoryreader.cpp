#include "directoryreader.h"

#include <iostream>
#include <dirent.h>

#include <glow/logging.h>



DirectoryReader::DirectoryReader():
    DirectoryReader("")
{

}

DirectoryReader::DirectoryReader(const std::string& path):
    m_path(path)
{

}

const std::string& DirectoryReader::path() const {
    return m_path;
}

void DirectoryReader::setPath(const std::string& path) {
    m_path = path;
}

std::list<std::string> DirectoryReader::read() const {
    std::list<std::string> files;
    std::string pathBase;

    if (m_path[m_path.size() - 1] == '/') {
        pathBase = m_path;
    } else {
        pathBase = m_path + "/";
    }


    DIR* directory = opendir(pathBase.c_str());
    if (directory == nullptr) {
        glow::critical("Failed to read directory '%;'", pathBase);
        return files; // In case glow::critical is replaced by non-exiting method
    }

    for (struct dirent* entity = readdir(directory); entity != nullptr; entity = readdir(directory)) {
        if (entity->d_type == DT_REG) {
            files.push_back(pathBase + entity->d_name);
        }
    }

    closedir(directory);

    return files;
}

