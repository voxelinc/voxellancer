#include "equipment.h"

Equipment::Equipment(const std::string& equipmentKey):
    m_equipmentKey(equipmentKey)
{
}

const std::string& Equipment::equipmentKey() const {
    return m_equipmentKey;
}

