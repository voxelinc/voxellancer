#include "directoryreader.h"

#include <iostream>

#include <tinydir.h>


DirectoryReader::DirectoryReader()
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

    tinydir_dir directory;

    if (tinydir_open(&directory, m_path.c_str())) {
        glow::critical("Failed to read directory '%;'", m_path);
    }

    std::cout << "Reading " << m_path << std::endl

    for (size_t i = 0; i < directory.n_files; i++) {
        tindir_file file;

        if (tinydir_readfile_n(&directory, &file, i)) {
            glow::critical("Failed to read entity %; in directory '%;'", i, m_path);
        }

        if (file.is_reg) {
            files.push_back(file.name);
        }

    }

    tinydir_close(&directory);
}

