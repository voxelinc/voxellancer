#pragma once

#include <string>


/**
 * Reads a whole directory of files as property-files
 * Prefixes the data from a file with the files basename,
 * e.g. a property "foo.name" in a file "/some/where/bar.ini"
 * will be stored in "bar.foo.name"
 */
class PropertyDirectory {
public:
    PropertyDirectory();
    PropertyDirectory(const std::string& path, const std::string& prefix = "");

    void read();


protected:
    std::string m_path;
    std::string m_prefix;
};

