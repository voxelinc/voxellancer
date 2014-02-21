#include "propertydirectory.h"

#include "utils/directoryreader.h"


PropertyDirectory::PropertyDirectory():
    PropertyDirectory("")
{

}

PropertyDirectory::PropertyDirectory(const std::string& path):
    m_path(path)
{

}
const std::string& PropertyDirectory::path() const {
    return m_path;
}

void PropertyDirectory::setPath(const std::string& path) {
    m_path = path;
}

void PropertyDirectory::read() {
    std::list<std::string> files = DirectoryReader(m_path).read();

    for (std::string& file : files) {

        PropertyManager::instance()->load(file, prefix);
    }
}

