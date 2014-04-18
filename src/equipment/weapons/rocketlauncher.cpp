#include "rocketlauncher.h"

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "equipment/hardpoint.h"

#include "physics/physics.h"

#include "property/property.h"

#include "resource/worldobjectbuilder.h"

#include "voxel/voxelclusterbounds.h"
#include "voxel/specialvoxels/hardpointvoxel.h"

#include "worldobject/worldobjectcomponents.h"

#include "world/world.h"
#include "world/god.h"

#include "physics/physics.h"
#include "voxel/voxelclusterbounds.h"
#include "utils/geometryhelper.h"

#include "sound/soundmanager.h"


RocketLauncher::RocketLauncher(const std::string& equipmentKey):
    Weapon(WeaponType::RocketLauncher, equipmentKey),
    m_cooldownTime(0)
{

}

const Visuals& RocketLauncher::visuals() const {
    return m_visuals;
}

void RocketLauncher::setVisuals(const Visuals& visuals) {
    m_visuals = visuals;
}

float RocketLauncher::cooldownTime() const {
    return m_cooldownTime;
}

void RocketLauncher::setCooldownTime(float cooldownTime) {
    m_cooldownTime = cooldownTime;
}

const std::string& RocketLauncher::rocketName() const {
    return m_rocketName;
}

void RocketLauncher::setRocketName(const std::string& rocketName) {
    m_rocketName = rocketName;
}

void RocketLauncher::fireAtObject(WorldObject* target) {
    if (canFire()) {
        Rocket* rocket = createRocket();
        setupRocket(rocket, target);

        World::instance()->god().scheduleSpawn(rocket);
        onFired();
    }
}

void RocketLauncher::update(float deltaSec) {
    Weapon::update(deltaSec);
}

void RocketLauncher::setupRocket(Rocket* rocket, WorldObject* target) {
    WorldObject* worldObject = hardpoint()->components()->worldObject();
    glm::quat launchOrientation = worldObject->transform().orientation() * GeometryHelper::quatFromViewDirection(hardpoint()->direction());
    float rocketLength = rocket->bounds().minimalGridAABB().extent(ZAxis) * rocket->transform().scale();
    glm::vec3 rocketPosition = hardpoint()->voxel()->position() + launchOrientation * glm::vec3(0, 0, -rocketLength / 2.0f);

    rocket->transform().setOrientation(launchOrientation);
    rocket->transform().setPosition(rocketPosition);

    rocket->setCreator(worldObject);
    rocket->setTarget(target);

    rocket->physics().setSpeed(worldObject->physics().speed());
}


Rocket* RocketLauncher::createRocket() {
    Rocket* rocket = WorldObjectBuilder(m_rocketName).buildRocket();
    return rocket;
}

