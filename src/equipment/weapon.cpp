#include "weapon.h"

#include <algorithm>

#include "utils/geometryhelper.h"

#include "voxel/specialvoxels/hardpointvoxel.h"

#include "equipment/hardpoint.h"
#include "equipment/weapons/projectile.h"


Weapon::Weapon(WeaponType type, const std::string& equipmentKey):
    Equipment(equipmentKey),
    m_type(type),
    m_cooldown(0.0f),
    m_cooldownTime(0.0f),
    m_hardpoint(nullptr)
{
}

Hardpoint* Weapon::hardpoint() {
    return m_hardpoint;
}

void Weapon::setHardpoint(Hardpoint* hardpoint) {
    m_hardpoint = hardpoint;
}

float Weapon::cooldownTime() const {
    return m_cooldownTime;
}

void Weapon::setCooldownTime(float cooldownTime) {
    m_cooldownTime = cooldownTime;
}

const Visuals& Weapon::visuals() const {
    return m_visuals;
}

void Weapon::setVisuals(const Visuals& visuals) {
    m_visuals = visuals;
}

const std::string Weapon::projectileName() const {
    return m_projectileName;
}

void Weapon::setProjectileName(const std::string& name) {
    m_projectileName = name;
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

