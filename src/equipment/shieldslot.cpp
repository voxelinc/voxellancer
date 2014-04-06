#include "shieldslot.h"

#include <iostream>

#include "shield.h"


ShieldSlot::ShieldSlot(WorldObjectComponents* components):
    WorldObjectSlot(components, 0)
{

}

std::shared_ptr<Shield>& ShieldSlot::shield() {
    return m_shield;
}

void ShieldSlot::setShield(const std::shared_ptr<Shield>& shield) {
    m_shield = shield;
}

void ShieldSlot::update(float deltaSec) {
    if (m_shield.get()) {
        m_shield->update(deltaSec);
    }
}

