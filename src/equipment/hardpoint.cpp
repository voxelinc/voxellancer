#include "hardpoint.h"

#include "utils/safenormalize.h"
#include "utils/geometryhelper.h"

#include "voxel/specialvoxels/hardpointvoxel.h"

#include "worldobject/worldobject.h"
#include "worldobject/worldobjectcomponents.h"

#include "weapon.h"



Hardpoint::Hardpoint(WorldObjectComponents* components, HardpointVoxel* voxel):
    WorldObjectSlot(components, voxel->group()),
    m_voxel(voxel),
    m_weapon(nullptr),
    m_direction(0, 0, -1)
{
}

HardpointVoxel* Hardpoint::voxel() {
    return m_voxel;
}

const std::shared_ptr<Weapon>& Hardpoint::weapon() {
    return m_weapon;
}

void Hardpoint::setWeapon(const std::shared_ptr<Weapon>& weapon) {
    m_weapon = weapon;
    if (m_weapon) {
        m_weapon->setHardpoint(this);
    }

    notifyObservers();
}

const glm::vec3& Hardpoint::direction() const {
    return m_direction;
}

void Hardpoint::setDirection(const glm::vec3& direction) {
    assert(normalizeable(direction));
    m_direction = glm::normalize(direction);
}

float Hardpoint::fieldOfAim() const {
    return m_fieldOfAim;
}

void Hardpoint::setFieldOfAim(float fieldOfAim) {
    m_fieldOfAim = fieldOfAim;
}

bool Hardpoint::inFieldOfAim(const glm::vec3& point) {
    if (!voxel()) {
        return false;
    }

    WorldObject* worldObject = m_components->worldObject();
    if(!worldObject) {
        return false;
    }

    glm::vec3 requiredWorldDirection = point - voxel()->position();
    glm::vec3 requiredLocalDirection = glm::inverse(worldObject->orientation()) * requiredWorldDirection;

    return GeometryHelper::angleBetween(requiredLocalDirection, m_direction) <= m_fieldOfAim;
}

void Hardpoint::update(float deltaSec) {
    if(m_weapon) {
        m_weapon->update(deltaSec);
    }
}

void Hardpoint::onVoxelRemoval() {
    m_components->removeHardpoint(this);
}

