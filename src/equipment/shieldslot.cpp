#include "shieldslot.h"

#include <cassert>

#include "equipmentchanger.h"
#include "shield.h"


ShieldSlot::ShieldSlot(WorldObjectComponents* components, int index):
    WorldObjectSlot(components, index)
{

}

std::shared_ptr<Shield>& ShieldSlot::shield() {
    return m_shield;
}

void ShieldSlot::setShield(const std::shared_ptr<Shield>& shield) {
    EquipmentChanger<ShieldSlot, Shield>(*this, m_shield, shield).change();
}

void ShieldSlot::update(float deltaSec) {
    if (m_shield) {
        m_shield->update(deltaSec);
    }
}

