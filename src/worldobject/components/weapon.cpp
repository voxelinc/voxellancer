#include "weapon.h"

#include <algorithm>
#include <iostream>

#include "utils/geometryhelper.h"

#include "voxel/specialvoxels/hardpointvoxel.h"

#include "worldobject/components/hardpoint.h"
#include "worldobject/components/weapons/projectile.h"


Weapon::Weapon(WeaponType type, const std::string& equipmentKey):
    Equipment(equipmentKey),
    m_type(type),
    m_cooldown(0.0f),
    m_hardpoint(nullptr)
{
}

Hardpoint* Weapon::hardpoint() {
    return m_hardpoint;
}

void Weapon::setHardpoint(Hardpoint* hardpoint) {
    m_hardpoint = hardpoint;
}

WeaponType Weapon::type() const {
    return m_type;
}

void Weapon::update(float deltaSec) {
    m_cooldown = std::max(m_cooldown - deltaSec, 0.0f);
}

bool Weapon::canFire() {
    return m_cooldown == 0.0f;
}

void Weapon::onFired() {
    m_cooldown = cooldownTime();
}

