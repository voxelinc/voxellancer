#pragma once

#include <string>


class Equipment {
public:
    Equipment(const std::string& equipmentKey);

    const std::string& equipmentKey() const;


protected:
    std::string m_equipmentKey;
};

