#include "propertydirectory.h"

#include <glow/logging.h>

#include "utils/directoryreader.h"

#include "def_regex.h"
#include "propertymanager.h"


PropertyDirectory::PropertyDirectory():
    PropertyDirectory("", "")
{

}

PropertyDirectory::PropertyDirectory(const std::string& path, const std::string& prefix):
    m_path(path),
    m_prefix(prefix)
{

}

void PropertyDirectory::read() {
    std::list<std::string> files = DirectoryReader(m_path).read();

    regexns::regex iniRegex(R"(^.*?([^\/\\]+)\.(.+)$)");

    for (std::string& file : files) {
        regexns::smatch matches;
        regexns::regex_match(file, matches, iniRegex);

        if (matches.size() < 3 || matches[2] != "ini") {
            glow::debug("'%;' is no .ini file, skipping", file);
            continue;
        }

        if (matches.size() > 1) {
            std::string basename = matches[1];
            std::string prefix = m_prefix.empty() ? basename : m_prefix + "." + basename;
            PropertyManager::instance()->load(file, prefix);
        }
    }
}


