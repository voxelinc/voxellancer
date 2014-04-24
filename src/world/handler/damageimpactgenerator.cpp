#include "damageimpactgenerator.h"

#include "worldobject/worldobject.h"

#include "utils/tostring.h"
#include "collision/voxelcollision.h"
#include "voxel/voxel.h"
#include "physics/physics.h"


void DamageImpactGenerator::parse(std::list<WorldObjectCollision>& worldObjectCollisions) {
    m_damageImpactAccumulator.clear();

    for(WorldObjectCollision& worldObjectCollision : worldObjectCollisions) {
        float massPerImpactA = worldObjectCollision.worldObjectA()->physics().mass() / worldObjectCollision.voxelCollisions().size();
        float massPerImpactB = worldObjectCollision.worldObjectB()->physics().mass() / worldObjectCollision.voxelCollisions().size();

        Transform targetTransformA(worldObjectCollision.worldObjectA()->transform(),
            worldObjectCollision.worldObjectA()->physics().speed().directional(),
            glm::quat(worldObjectCollision.worldObjectA()->physics().speed().angular()));

        Transform targetTransformB(worldObjectCollision.worldObjectB()->transform(),
            worldObjectCollision.worldObjectB()->physics().speed().directional(),
            glm::quat(worldObjectCollision.worldObjectB()->physics().speed().angular()));

        for(VoxelCollision& voxelCollision :  worldObjectCollision.voxelCollisions()) {
            glm::vec3 speedA = targetTransformA.applyTo(glm::vec3(voxelCollision.a().voxel()->gridCell())) - worldObjectCollision.worldObjectA()->transform().applyTo(glm::vec3(voxelCollision.a().voxel()->gridCell()));
            glm::vec3 speedB = targetTransformB.applyTo(glm::vec3(voxelCollision.b().voxel()->gridCell())) - worldObjectCollision.worldObjectB()->transform().applyTo(glm::vec3(voxelCollision.b().voxel()->gridCell()));

            if (voxelCollision.a().worldObject()->spawnState() != SpawnState::RemovalScheduled) {
                m_damageImpactAccumulator.parse(DamageImpact(voxelCollision.a().worldObject(),
                                                             voxelCollision.a().voxel(),
                                                             (speedB - speedA) * (massPerImpactB) * 10000.0f,
                                                             voxelCollision.b().worldObject()->collisionFieldOfDamage()));
            }
            if (voxelCollision.b().worldObject()->spawnState() != SpawnState::RemovalScheduled) {
                m_damageImpactAccumulator.parse(DamageImpact(voxelCollision.b().worldObject(),
                                                             voxelCollision.b().voxel(),
                                                             (speedA - speedB) * (massPerImpactA)* 10000.0f,
                                                             voxelCollision.a().worldObject()->collisionFieldOfDamage()));
            }
        }
    }
}

std::list<DamageImpact>& DamageImpactGenerator::damageImpacts() {
    return m_damageImpactAccumulator.accumulatables();
}
