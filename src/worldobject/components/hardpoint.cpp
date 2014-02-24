#include "hardpoint.h"

#include "voxel/specialvoxels/hardpointvoxel.h"

#include "worldobject/worldobjectcomponents.h"

#include "weapon.h"



Hardpoint::Hardpoint(WorldObjectComponents* components, HardpointVoxel* voxel):
    WorldObjectSlot(components, voxel, voxel->index()),
    m_weapon(nullptr)
{
}

const std::shared_ptr<Weapon>& Hardpoint::weapon() {
    return m_weapon;
}

void Hardpoint::setWeapon(const std::shared_ptr<Weapon>& weapon) {
    m_weapon = weapon;
    m_weapon->setHardpoint(this);
}

const glm::vec3& Hardpoint::direction() const {
    return m_direction;
}

void Hardpoint::setDirection(const glm::vec3& direction) {
    m_direction = direction;
}

const glm::vec2& Hardpoint::fieldOfAim() const {
    return m_fieldOfAim;
}

void Hardpoint::setFieldOfAim(const glm::vec2& fieldOfAim) {
    m_fieldOfAim = fieldOfAim;
}

void Hardpoint::update(float deltaSec) {
    if(m_weapon) {
        m_weapon->update(deltaSec);
    }
}


