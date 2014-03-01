#include "rocketlauncher.h"

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "equipment/hardpoint.h"

#include "physics/physics.h"

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
    glm::quat launchOrientation = worldObject->transform().orientation() * GeometryHelper::quatFromViewDirection(hardpoint()->direction());
    float rocketLength = rocket->bounds().minimalGridAABB().extent(ZAxis) * rocket->transform().scale();
    glm::vec3 rocketPosition = hardpoint()->voxel()->position() + launchOrientation * glm::vec3(0, 0, -rocketLength / 2.0f);

    rocket->transform().setOrientation(launchOrientation);
    rocket->transform().setPosition(rocketPosition);

    rocket->setCreator(worldObject);
    rocket->setTarget(target);

    rocket->physics().setSpeed(worldObject->physics().speed());
}

