#include "rocketlauncher.h"

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "voxel/specialvoxels/hardpointvoxel.h"

#include "equipment/hardpoint.h"

#include "world/world.h"
#include "world/god.h"


RocketLauncher::RocketLauncher(const std::string& equipmentKey):
    Weapon(WeaponType::RocketLauncher, equipmentKey)
{

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
    glm::quat shipOrientation = worldObject->transform().orientation();
    float rocketLength = rocket->bounds().minimalGridAABB().extent(ZAxis) * rocket->transform().scale();

    rocket->transform().setOrientation(shipOrientation);
    rocket->transform().setPosition(hardpoint()->voxel()->position() + shipOrientation * glm::vec3(0, 0, -rocketLength / 2.0f));

    rocket->setCreator(worldObject);
    rocket->setTarget(target);

    rocket->physics().setSpeed(worldObject->physics().speed());
}

