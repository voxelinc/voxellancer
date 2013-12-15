#include "elasticimpulsegenerator.h"

#include <iostream>
#include <cassert>

#include "worldobject/worldobject.h"

#include "utils/tostring.h"


void ElasticImpulseGenerator::parse(std::list<WorldObjectCollision>& worldObjectCollisions) {
    m_worldObjectImpulses.clear();

    for(WorldObjectCollision& worldObjectCollision : worldObjectCollisions) {
        assert(worldObjectCollision.voxelCollisions().size() > 0);

        VoxelCollision voxelCollision = worldObjectCollision.voxelCollisions().front();

        generateImpulse(voxelCollision.a(), voxelCollision.b());
        generateImpulse(voxelCollision.b(), voxelCollision.a());
    }
}

std::list<Impulse>& ElasticImpulseGenerator::worldObjectImpulses() {
    return m_worldObjectImpulses;
}

void ElasticImpulseGenerator::generateImpulse(VoxelCollisionParticipant &from, VoxelCollisionParticipant &to) {
    WorldTransform targetTransformFrom(from.worldObject()->transform(), from.worldObject()->physics().speed(), glm::quat(from.worldObject()->physics().angularSpeed()));
    glm::vec3 speed = targetTransformFrom.applyTo(glm::vec3(from.voxel()->gridCell())) - from.worldObject()->transform().applyTo(glm::vec3(from.voxel()->gridCell()));
    glm::vec3 normal = glm::normalize(to.worldObject()->transform().applyTo(glm::vec3(to.voxel()->gridCell())) - from.worldObject()->transform().applyTo(glm::vec3(from.voxel()->gridCell())));

    m_worldObjectImpulses.push_back(Impulse(to.worldObject(), to.voxel(), speed, from.worldObject()->physics().mass(), normal));
}

