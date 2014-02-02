#include "hardpoint.h"

#include "voxel/specialvoxels/hardpointvoxel.h"

#include "worldobject/components/weapon.h"
#include "worldobject/worldobjectcomponents.h"


Hardpoint::Hardpoint(WorldObjectComponents* components, HardpointVoxel* voxel):
    WorldObjectSlot(components, voxel->index()),
    m_voxel(voxel),
    m_weapon(nullptr)
{
}

HardpointVoxel* Hardpoint::voxel() {
    return m_voxel;
}

Weapon* Hardpoint::weapon() {
    return m_weapon;
}

void Hardpoint::setWeapon(Weapon* weapon) {
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

void Hardpoint::onVoxelRemoval() {
    m_components->removeHardpoint(this);
}

