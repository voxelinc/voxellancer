#include "voxelparticleintersectioncheck.h"

#include "geometry/point.h"
#include "geometry/transform.h"

#include "world/world.h"

#include "worldobject/worldobject.h"

#include "worldtree/worldtreegeode.h"
#include "worldtree/worldtreequery.h"

#include "voxelparticledata.h"
#include "voxelparticleworld.h"

VoxelParticleIntersectionCheck::VoxelParticleIntersectionCheck(VoxelParticleWorld* world):
    VoxelParticleRemoveCheck(world),
    m_fullDeadCheckInterval("vfx.fullDeadCheckInterval")
{
}

void VoxelParticleIntersectionCheck::update(float deltaSec) {
    setInterval(m_fullDeadCheckInterval);
    VoxelParticleRemoveCheck::update(deltaSec);
}

bool VoxelParticleIntersectionCheck::check(VoxelParticleData* particleData) {
	float timeDelta = m_world->time() - particleData->creationTime;
    glm::vec3 position = particleData->directionalSpeed * timeDelta + particleData->creationPosition;

    Point voxelPoint(position); // approximate a point
    WorldTreeQuery query(&World::instance()->worldTree(), &voxelPoint);

    for (WorldTreeGeode* geode : query.nearGeodes()) {
        WorldObject* worldObject = geode->worldObject();
        glm::ivec3 cell = glm::ivec3(worldObject->transform().inverseApplyTo(position));
        if (worldObject->voxel(cell)) {
            return true;
        }
    }

    return false;
}
