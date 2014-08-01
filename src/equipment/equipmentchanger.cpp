#include "equipmentchanger.h"

#include "engine.h"
#include "shield.h"
#include "weapon.h"


template<>
void EquipmentChanger<EngineSlot, Engine>::setSlot(Engine& engine, EngineSlot* slot) {
    engine.setEngineSlot(slot);
}

template<>
void EquipmentChanger<Hardpoint, Weapon>::setSlot(Weapon& weapon, Hardpoint* hardpoint) {
    weapon.setHardpoint(hardpoint);
}

template<>
void EquipmentChanger<ShieldSlot, Shield>::setSlot(Shield& shield, ShieldSlot* slot) {
    shield.setShieldSlot(slot);
}

