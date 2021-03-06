#include "directoryreader.h"

#include <stdexcept>

#include <glow/logging.h>

#include "def_filesystem.h"


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

    filesystem::path path(m_path);

    if (filesystem::exists(path) && filesystem::is_directory(path)) {
        filesystem::directory_iterator end;
        for (filesystem::directory_iterator iter(path); iter != end; ++iter) {
            if (filesystem::is_regular_file(iter->status())) {
                files.push_back(iter->path().string());
            }
        }
    }

    return files;
}

