#include "worldobjectequipment.h"

WorldObjectEquipment::WorldObjectEquipment(const std::string& key):
    m_key(key)
{
}

const std::string& WorldObjectEquipment::key() const {
    return m_key;
}

