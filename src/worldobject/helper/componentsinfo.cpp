#include "componentsinfo.h"

#include "worldobject/worldobject.h"
#include "worldobject/worldobjectcomponents.h"

#include "equipment/hardpoint.h"
#include "equipment/weapons/gun.h"
#include "equipment/weapons/rocketlauncher.h"
#include "equipment/engine.h"

ComponentsInfo::ComponentsInfo(WorldObject* worldObject) :
    m_worldObject(worldObject)  
{
    updateInfo();
    m_maxBulletRange = 0;
    m_maxForwardSpeed = 0;
    m_maxRocketRange = 0;
}

void ComponentsInfo::updateInfo() {
    m_maxBulletRange = 0;
    m_maxForwardSpeed = 0;
    m_maxRocketRange = 0;
    for (std::shared_ptr<Hardpoint> hardpoint : m_worldObject->components().hardpoints()) {
        if (hardpoint->weapon()) {
            if (hardpoint->weapon()->type() == WeaponType::Gun) {
                glm::max(dynamic_cast<Gun*>(hardpoint->weapon().get())->bulletSpeed()*dynamic_cast<Gun*>(hardpoint->weapon().get())->bulletLifetime(), m_maxBulletRange);
            }
            if (hardpoint->weapon()->type() == WeaponType::RocketLauncher) {
                glm::max(dynamic_cast<RocketLauncher*>(hardpoint->weapon().get())-> *dynamic_cast<Gun*>(hardpoint->weapon().get())->bulletLifetime(), m_maxBulletRange);
            }
        }
    }
}

float ComponentsInfo::maxBulletRange() {
    return m_maxBulletRange;
}

float ComponentsInfo::maxRocketRange() {
    return m_maxRocketRange;
}

float ComponentsInfo::maxForwardSpeed() {
    return m_maxForwardSpeed;
}
    /*float maxBulletRange();
    float maxRocketRange();
    float maxForwardSpeed();

    void updateInfo();

private:
    const WorldObject* worldObject;*/