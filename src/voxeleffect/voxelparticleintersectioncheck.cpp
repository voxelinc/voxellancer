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
    m_particleEngine(engine)
{
}

bool VoxelParticleIntersectionCheck::isDead(const VoxelParticleData& particleData) {
	float timeDelta = m_particleEngine->time() - particleData.creationTime;
    glm::vec3 position = particleData.directionalSpeed * timeDelta + particleData.creationPosition;

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
