#pragma once

#include <list>
#include <string>


class DirectoryReader {
public:
    DirectoryReader();
    DirectoryReader(const std::string& path);

    /*
        Return the list of files in &path,
        non-recursive
    */
    std::list<std::string> read() const;


protected:
    std::string m_path;
};

