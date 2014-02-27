#include "equipment.h"

Equipment::Equipment(const std::string& equipmentKey):
    m_equipmentKey(equipmentKey)
{
}

Equipment::~Equipment() = default;

const std::string& Equipment::equipmentKey() const {
    return m_equipmentKey;
}

