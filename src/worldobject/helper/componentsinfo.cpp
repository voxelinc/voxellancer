#include "componentsinfo.h"

#include "worldobject/worldobject.h"
#include "worldobject/worldobjectcomponents.h"

#include "equipment/hardpoint.h"
#include "equipment/weapons/gun.h"
#include "equipment/weapons/rocketlauncher.h"
#include "equipment/engine.h"
#include "equipment/enginepower.h"

ComponentsInfo::ComponentsInfo(WorldObject* worldObject) :
    m_worldObject(worldObject)  
{
    m_maxBulletRange = 0;
    m_maxForwardSpeed = 0;
}

void ComponentsInfo::updateInfo() {
    for (std::shared_ptr<Hardpoint> hardpoint : m_worldObject->components().hardpoints()) {
        if (hardpoint->weapon()) {
            if (hardpoint->weapon()->type() == WeaponType::Gun) {
                Gun* gun = static_cast<Gun*>(hardpoint->weapon().get());
                m_maxBulletRange = glm::max(gun->bulletSpeed()*gun->bulletLifetime(), m_maxBulletRange);
            }
        }
    }
    m_maxForwardSpeed = m_worldObject->components().enginePower().directional().x;
}

const float ComponentsInfo::maxBulletRange() const {
    return m_maxBulletRange;
}

const float ComponentsInfo::maxForwardSpeed() const {
    return m_maxForwardSpeed;
}