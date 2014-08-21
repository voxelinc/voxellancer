#include "impulsegenerator.h"

#include <cassert>

#include "collision/voxelcollision.h"

#include "physics/physics.h"

#include "utils/safenormalize.h"

#include "voxel/voxel.h"

#include "worldobject/worldobject.h"


void ImpulseGenerator::parse(std::list<WorldObjectCollision>& worldObjectCollisions) {
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

std::list<Impulse>& ImpulseGenerator::worldObjectImpulses() {
    return m_worldObjectImpulses;
}

void ImpulseGenerator::generateImpulse(VoxelCollisionParticipant &from, VoxelCollisionParticipant &to) {
    Transform targetTransformFrom(from.worldObject()->transform(),
        from.worldObject()->physics().speed().directional(),
        glm::quat(from.worldObject()->physics().speed().angular()));

    glm::vec3 speed = targetTransformFrom.applyTo(
        glm::vec3(from.voxel()->cell())) -
        from.worldObject()->transform().applyTo(glm::vec3(from.voxel()->cell()));

    glm::vec3 normal = safeNormalize(
        to.worldObject()->transform().applyTo(glm::vec3(to.voxel()->cell())) -
        from.worldObject()->transform().applyTo(glm::vec3(from.voxel()->cell())), glm::vec3(0.0f, 0.0f, 1.0f));

    m_worldObjectImpulses.push_back(Impulse(to.worldObject(), to.voxel(), speed, from.worldObject()->physics().mass(), normal));
}

