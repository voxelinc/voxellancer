#include "propertydirectory.h"

#include "utils/directoryreader.h"

#include "def_regex.h"
#include "propertymanager.h"


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

    regexns::regex iniRegex(R"(^.*?/?([a-zA-Z0-9_-]*)\.([a-zA-Z0-9_-]*)$)");

    for (std::string& file : files) {
        regexns::smatch matches;
        regexns::regex_match(file, matches, iniRegex);

        assert(matches.size() > 1);

        std::string basename = matches[1];
        PropertyManager::instance()->load(file, basename);
    }
}


