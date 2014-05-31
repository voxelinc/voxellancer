#pragma once

#include <string>
#include <vector>


class StringHelper final {
public:
    StringHelper(const std::string& value);

    std::vector<std::string> split(char delimiter) const;


protected:
    std::string m_value;
};
