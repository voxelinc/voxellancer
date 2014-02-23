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

void PropertyDirectory::read() {
    std::list<std::string> files = DirectoryReader(m_path).read();

    regexns::regex iniRegex(R"(^.*?([^\/]+)\.ini$)");

    for (std::string& file : files) {
        regexns::smatch matches;
        regexns::regex_match(file, matches, iniRegex);

        if (matches.size() > 0) {
            std::string basename = matches[1];
            PropertyManager::instance()->load(file, basename);
        }
    }
}


