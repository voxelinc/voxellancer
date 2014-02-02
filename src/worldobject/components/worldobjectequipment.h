#pragma once

#include <string>


class WorldObjectEquipment {
public:
    WorldObjectEquipment(const std::string& key);

    const std::string& key() const;


protected:
    std::string m_key;
};

