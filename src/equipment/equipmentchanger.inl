#pragma once

#include <cassert>


template<typename EquipmentSlotType, typename EquipmentType>
EquipmentChanger<EquipmentSlotType, EquipmentType>::EquipmentChanger(EquipmentSlotType& slot, std::shared_ptr<EquipmentType>& target, const std::shared_ptr<EquipmentType>& newEquipment):
    m_slot(slot),
    m_target(target),
    m_newEquipment(newEquipment)
{
}

template<typename EquipmentSlotType, typename EquipmentType>
void EquipmentChanger<EquipmentSlotType, EquipmentType>::change() {
    assert(m_slot.mountable(m_newEquipment->equipmentKey()));

    if (m_target == m_newEquipment) {
        return;
    }

    if (m_target) {
        setSlot(*m_target, nullptr);
    }

    if (m_newEquipment) {
        setSlot(*m_newEquipment, &m_slot);
    }

    m_target = m_newEquipment;

    m_slot.notifyObservers();
}


