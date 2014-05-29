#include "shieldslot.h"

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
    m_shield = shield;
    notifyObservers();
}

void ShieldSlot::update(float deltaSec) {
    if (m_shield) {
        m_shield->update(deltaSec);
    }
}

