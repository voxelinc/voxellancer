#include "voxelparticleintersectioncheck.h"

#include "geometry/point.h"
#include "geometry/sphere.h"
#include "geometry/transform.h"

#include "world/world.h"

#include "worldobject/worldobject.h"

#include "worldtree/worldtreegeode.h"
#include "worldtree/worldtreenode.h"
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
bool VoxelParticleIntersectionCheck::check(VoxelParticleData* particle) {
	float timeDelta = m_engine->time() - particle->creationTime;
    glm::vec3 position = particle->directionalSpeed * timeDelta + particle->creationPosition;

    if (particle->scale <= 1.0f) {
        Point voxelPoint(position); // approximate a point
        WorldTreeQuery query(&World::instance()->worldTree(), &voxelPoint, particle->worldTreeNode);

        std::unordered_set<WorldTreeGeode*> nearGeodes(query.nearGeodes());
      //  particle->worldTreeNode = query.lastNode();

        for (WorldTreeGeode* geode : nearGeodes) {
            WorldObject* worldObject = geode->worldObject();
            glm::ivec3 cell = glm::ivec3(worldObject->transform().inverseApplyTo(position));
            if (worldObject->voxel(cell)) {
                return true;
            }
        }
        return false;
    } else {
        Sphere voxelSphere(position, particle->scale / 2.0f); // approximate a sphere

        WorldTreeQuery query(&World::instance()->worldTree(), &voxelSphere, particle->worldTreeNode);

        bool intersections = query.areVoxelsIntersecting();
     //   particle->worldTreeNode = query.lastNode();

        return intersections;
    }
}

/*
    Intersection tests are considered to be performance-heavy and to simplify it
    they are always performed multithreaded.
    Might be worth to test out a threshold here however.
*/
bool VoxelParticleIntersectionCheck::isParallel(int checkCount) {
    return true;
}
