#include "directoryreader.h"

#include <stdexcept>

#ifdef WIN32
#include <windows.h>
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
    WIN32_FIND_DATA findfiledata;
    HANDLE hFind = INVALID_HANDLE_VALUE;

    std::wstring wpath(pathBase.begin(), pathBase.end());
    hFind = FindFirstFile((wpath + L"*").c_str(), &findfiledata);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if ((findfiledata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
                std::wstring file(findfiledata.cFileName);
                files.push_back(pathBase + std::string(file.begin(), file.end()));
            }
        }
        while (FindNextFile(hFind, &findfiledata) != 0);
    } else {
        glow::critical("Failed to read directory '%;'", pathBase);
        throw std::runtime_error(std::string("Directory '" + pathBase + "' not found!"));
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

