#include "damageimpactgenerator.h"

#include "worldobject/worldobject.h"

#include "utils/tostring.h"


void DamageImpactGenerator::parse(std::list<WorldObjectCollision>& worldObjectCollisions) {
    m_damageImpactAccumulator.clear();

    for(WorldObjectCollision& worldObjectCollision : worldObjectCollisions) {
        float massPerImpactA = worldObjectCollision.worldObjectA()->physics().mass() / worldObjectCollision.voxelCollisions().size();
        float massPerImpactB = worldObjectCollision.worldObjectB()->physics().mass() / worldObjectCollision.voxelCollisions().size();

        WorldTransform targetTransformA(worldObjectCollision.worldObjectA()->transform(), worldObjectCollision.worldObjectA()->physics().speed(), glm::quat(worldObjectCollision.worldObjectA()->physics().angularSpeed()));
        WorldTransform targetTransformB(worldObjectCollision.worldObjectB()->transform(), worldObjectCollision.worldObjectB()->physics().speed(), glm::quat(worldObjectCollision.worldObjectB()->physics().angularSpeed()));

        for(VoxelCollision& voxelCollision :  worldObjectCollision.voxelCollisions()) {
            glm::vec3 speedA = targetTransformA.applyTo(glm::vec3(voxelCollision.a().voxel()->gridCell())) - worldObjectCollision.worldObjectA()->transform().applyTo(glm::vec3(voxelCollision.a().voxel()->gridCell()));
            glm::vec3 speedB = targetTransformB.applyTo(glm::vec3(voxelCollision.b().voxel()->gridCell())) - worldObjectCollision.worldObjectB()->transform().applyTo(glm::vec3(voxelCollision.b().voxel()->gridCell()));

            if (!voxelCollision.a().worldObject()->scheduledForDeletion())
                m_damageImpactAccumulator.parse(DamageImpact(voxelCollision.a().worldObject(), voxelCollision.a().voxel(), (speedB - speedA) * (massPerImpactB)));
            if (!voxelCollision.b().worldObject()->scheduledForDeletion())
                m_damageImpactAccumulator.parse(DamageImpact(voxelCollision.b().worldObject(), voxelCollision.b().voxel(), (speedA - speedB) * (massPerImpactA)));
        }
    }
}

std::list<DamageImpact>& DamageImpactGenerator::damageImpacts() {
    return m_damageImpactAccumulator.accumulatables();
}
