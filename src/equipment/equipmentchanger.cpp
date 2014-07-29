#include "equipmentchanger.h"

#include "engine.h"
#include "shield.h"
#include "weapon.h"


template<>
void EquipmentChanger<EngineSlot, Engine>::setSlot(EngineSlot * slot) {
    m_target->setEngineSlot(slot);
}

template<>
void EquipmentChanger<Hardpoint, Weapon>::setSlot(Hardpoint * hardpoint) {
    m_target->setHardpoint(hardpoint);
}

template<>
void EquipmentChanger<ShieldSlot, Shield>::setSlot(ShieldSlot * slot) {
    m_target->setShieldSlot(slot);
}
