#include "stringhelper.h"

#include <sstream>


StringHelper::StringHelper(const std::string& value):
    m_value(value)
{
}

std::vector<std::string> StringHelper::split(char delimiter) const {
    std::vector<std::string> result;

    std::stringstream stream(m_value);
    std::string item;

    while (std::getline(stream, item, delimiter)) {
        result.push_back(item);
    }

    return result;
}


