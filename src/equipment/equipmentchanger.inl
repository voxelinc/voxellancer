#pragma once

#include <cassert>

#include "engine.h"
#include "shield.h"
#include "weapon.h"


template<typename EquipmentSlotType, typename EquipmentType>
EquipmentChanger<EquipmentSlotType, EquipmentType>::EquipmentChanger(EquipmentSlotType& slot, std::shared_ptr<EquipmentType>& target, const std::shared_ptr<EquipmentType>& equipment):
    m_slot(slot),
    m_target(target),
    m_equipment(equipment)
{
}

template<typename EquipmentSlotType, typename EquipmentType>
void EquipmentChanger<EquipmentSlotType, EquipmentType>::change() {
    assert(m_slot.mountable(m_equipment->equipmentKey()));

    bool changed = m_target != m_equipment;

    if (changed && m_target) {
        setSlot(nullptr);
    }

    m_target = m_equipment;

    if (m_target) {
        setSlot(&m_slot);
    }

    if (changed) {
        m_slot.notifyObservers();
    }
}


