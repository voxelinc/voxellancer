#pragma once

#include <list>
#include <string>


class DirectoryReader {
public:
    DirectoryReader();
    DirectoryReader(const std::string& path);

    const std::string& path() const;
    void setPath(const std::string& path);

    /*
        Return the list of files in &path,
        non-recursive
    */
    std::list<std::string> read() const;


protected:
    std::string m_path;
};

