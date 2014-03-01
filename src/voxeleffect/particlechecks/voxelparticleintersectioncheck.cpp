#include "voxelparticleintersectioncheck.h"

#include "geometry/point.h"
#include "geometry/sphere.h"
#include "geometry/transform.h"

#include "world/world.h"

#include "worldobject/worldobject.h"

#include "worldtree/worldtreegeode.h"
#include "worldtree/worldtreequery.h"

#include "voxeleffect/voxelparticledata.h"
#include "voxeleffect/voxelparticleengine.h"

#include "player.h"
#include "camera/camerahead.h"

VoxelParticleIntersectionCheck::VoxelParticleIntersectionCheck(const VoxelParticleEngine& engine) :
    m_particleEngine(engine),
    m_maxCheckDistance("particle.maxIntersectionCheckDistance")
{
}

bool VoxelParticleIntersectionCheck::isDead(const VoxelParticleData& particleData) {
	float timeDelta = m_particleEngine.time() - particleData.creationTime;
    glm::vec3 position = particleData.directionalSpeed * timeDelta + particleData.creationPosition;

    assert(m_player);
    if (isFarAway(position) || isBehindPlayer(position)) {
        return false;
    }

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

void VoxelParticleIntersectionCheck::setPlayer(const Player& player) {
    m_player = &player;
}

bool VoxelParticleIntersectionCheck::isFarAway(const glm::vec3& position) {
    float distance = glm::length(position - m_player->cameraHead().position());
    return distance > m_maxCheckDistance;
}

bool VoxelParticleIntersectionCheck::isBehindPlayer(const glm::vec3& position) {
    // maybe even extend to frustum check
    glm::vec3 playerToParticle = position - m_player->cameraHead().position();
    glm::vec3 inCameraCoord = glm::inverse(m_player->cameraHead().orientation()) * playerToParticle;
    return inCameraCoord.z > 0;
}
