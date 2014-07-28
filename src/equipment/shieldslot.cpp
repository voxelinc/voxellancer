#include "shieldslot.h"

#include <cassert>
#include <iostream>

#include "shield.h"


ShieldSlot::ShieldSlot(WorldObjectComponents* components, int index):
    WorldObjectSlot(components, index)
{

}

std::shared_ptr<Shield>& ShieldSlot::shield() {
    return m_shield;
}

void ShieldSlot::setShield(const std::shared_ptr<Shield>& shield) {
    assert(mountable(shield->equipmentKey()));

    bool changed = m_shield != shield;

    if (changed && m_shield) {
        m_shield->setShieldSlot(nullptr);
    }

    m_shield = shield;

    if (m_shield) {
        m_shield->setShieldSlot(this);
    }

    if (changed) {
        notifyObservers();
    }
}

void ShieldSlot::update(float deltaSec) {
    if (m_shield) {
        m_shield->update(deltaSec);
    }
}

