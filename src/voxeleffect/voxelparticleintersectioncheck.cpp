#include "voxelparticleintersectioncheck.h"

#include "geometry/point.h"
#include "geometry/sphere.h"
#include "geometry/transform.h"

#include "world/world.h"

#include "worldobject/worldobject.h"

#include "worldtree/worldtreegeode.h"
#include "worldtree/worldtreequery.h"

#include "voxelparticledata.h"
#include "voxelparticleengine.h"

VoxelParticleIntersectionCheck::VoxelParticleIntersectionCheck(VoxelParticleEngine* engine):
    VoxelParticleRemoveCheck(engine),
    m_fullDeadCheckInterval("vfx.fullIntersectionCheckInterval")
{
}

void VoxelParticleIntersectionCheck::update(float deltaSec) {
    setInterval(m_fullDeadCheckInterval);
    VoxelParticleRemoveCheck::update(deltaSec);
}

/*
    This check roughly distinguishes between small and big particles and removes the former
    faster, the later more accurate
*/
bool VoxelParticleIntersectionCheck::check(VoxelParticleData* particleData) {
	float timeDelta = m_world->time() - particleData->creationTime;
    glm::vec3 position = particleData->directionalSpeed * timeDelta + particleData->creationPosition;

    Point voxelPoint(position); // approximate as point
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
