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

    if (particleData->scale <= 1.0f) {
        Point voxelPoint(position); // approximate a point
        WorldTreeQuery query(&World::instance()->worldTree(), &voxelPoint);

        for (WorldTreeGeode* geode : query.nearGeodes()) {
            WorldObject* worldObject = geode->worldObject();
            glm::ivec3 cell = glm::ivec3(worldObject->transform().inverseApplyTo(position));
            if (worldObject->voxel(cell)) {
                return true;
            }
        }
    } else {
        Sphere voxelSphere(position, particleData->scale / 2.0f); // approximate a sphere
        WorldTreeQuery query(&World::instance()->worldTree(), &voxelSphere);
        return query.areVoxelsIntersecting();
    }
    return false;
}

/*
    Intersection tests are considered to be performance-heavy and to simplify it
    they are always performed multithreaded.
    Might be worth to test out a threshold here however.
*/
bool VoxelParticleIntersectionCheck::isParallel(int checkCount) {
    return true;
}

