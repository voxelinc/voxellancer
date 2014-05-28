#include "componentsinfo.h"

#include "worldobject/worldobject.h"
#include "worldobject/worldobjectcomponents.h"

#include "equipment/hardpoint.h"
#include "equipment/weapons/gun.h"
#include "equipment/weapons/rocketlauncher.h"
#include "equipment/engine.h"
#include "equipment/enginepower.h"

ComponentsInfo::ComponentsInfo(WorldObjectComponents* components) :
    m_components(components)  
{
    components->addObserver(this);
    m_maxRocketRange = 0;
    m_maxBulletRange = 0;
    m_maxForwardSpeed = 0;
}

void ComponentsInfo::updateInfo() {
    for (std::shared_ptr<Hardpoint> hardpoint : m_components->hardpoints()) {
        if (hardpoint->weapon()) {
            if (hardpoint->weapon()->type() == WeaponType::Gun) {
                Gun* gun = static_cast<Gun*>(hardpoint->weapon().get());
                m_maxBulletRange = glm::max(gun->bulletSpeed()*gun->bulletLifetime(), m_maxBulletRange);
            } else if (hardpoint->weapon()->type() == WeaponType::RocketLauncher) {
                RocketLauncher* launcher = static_cast<RocketLauncher*>(hardpoint->weapon().get());
                m_maxRocketRange = glm::max(launcher->rocketRange(), m_maxRocketRange);
            }
        }
    }
    m_maxForwardSpeed = m_components->enginePower().directional().x;
}

float ComponentsInfo::maxBulletRange() const {
    return m_maxBulletRange;
}

float ComponentsInfo::maxForwardSpeed() const {
    return m_maxForwardSpeed;
}

float ComponentsInfo::maxRocketRange() const {
    return m_maxRocketRange;
}

void ComponentsInfo::updateObserver() {
    updateInfo();
}