#include "elasticimpulsegenerator.h"

#include <cassert>

#include "collision/voxelcollision.h"

#include "physics/physics.h"

#include "utils/glmext/safenormalize.h"

#include "voxel/voxel.h"

#include "worldobject/worldobject.h"


void ElasticImpulseGenerator::parse(std::list<WorldObjectCollision>& worldObjectCollisions) {
    m_worldObjectImpulses.clear();

    for(WorldObjectCollision& worldObjectCollision : worldObjectCollisions) {
        assert(worldObjectCollision.voxelCollisions().size() > 0);

        VoxelCollision voxelCollision = worldObjectCollision.voxelCollisions().front();

        if (voxelCollision.b().worldObject()->spawnState() != SpawnState::RemovalScheduled) {
            generateImpulse(voxelCollision.a(), voxelCollision.b());
        }
        if (voxelCollision.a().worldObject()->spawnState() != SpawnState::RemovalScheduled) {
            generateImpulse(voxelCollision.b(), voxelCollision.a());
        }
    }
}

std::list<Impulse>& ElasticImpulseGenerator::worldObjectImpulses() {
    return m_worldObjectImpulses;
}

void ElasticImpulseGenerator::generateImpulse(VoxelCollisionParticipant &from, VoxelCollisionParticipant &to) {
    Transform targetTransformFrom(from.worldObject()->transform(),
        from.worldObject()->physics().speed().directional(),
        glm::quat(from.worldObject()->physics().speed().angular()));

    glm::vec3 speed = targetTransformFrom.applyTo(
        glm::vec3(from.voxel()->gridCell())) -
        from.worldObject()->transform().applyTo(glm::vec3(from.voxel()->gridCell()));

    glm::vec3 normal = safeNormalize(
        to.worldObject()->transform().applyTo(glm::vec3(to.voxel()->gridCell())) -
        from.worldObject()->transform().applyTo(glm::vec3(from.voxel()->gridCell())));

    m_worldObjectImpulses.push_back(Impulse(to.worldObject(), to.voxel(), speed, from.worldObject()->physics().mass(), normal));
}

