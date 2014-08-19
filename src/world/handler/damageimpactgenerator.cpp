#include "damageimpactgenerator.h"

#include "collision/voxelcollision.h"

#include "physics/physics.h"

#include "voxel/voxel.h"

#include "worldobject/worldobject.h"
#include "worldobject/worldobjectinfo.h"


DamageImpactGenerator::DamageImpactGenerator():
    m_elasticity("physics.elasticity")
{
}

void DamageImpactGenerator::parse(std::list<WorldObjectCollision>& worldObjectCollisions) {
    m_damageImpactAccumulator.clear();

    for(WorldObjectCollision& worldObjectCollision : worldObjectCollisions) {
        WorldObject* worldObjectA = worldObjectCollision.worldObjectA();
        WorldObject* worldObjectB = worldObjectCollision.worldObjectB();

        float m1 = worldObjectA->physics().mass() / worldObjectCollision.voxelCollisions().size();
        float m2 = worldObjectB->physics().mass() / worldObjectCollision.voxelCollisions().size();

        Transform targetTransformA = worldObjectA->physics().speed().moved(worldObjectA->transform(), 1.0f);
        Transform targetTransformB = worldObjectB->physics().speed().moved(worldObjectB->transform(), 1.0f);

        for(VoxelCollision& voxelCollision :  worldObjectCollision.voxelCollisions()) {
            glm::vec3 v1 = targetTransformA.applyTo(glm::vec3(voxelCollision.a().voxel()->gridCell())) - voxelCollision.a().voxel()->position();
            glm::vec3 v2 = targetTransformB.applyTo(glm::vec3(voxelCollision.b().voxel()->gridCell())) - voxelCollision.b().voxel()->position();

            float speedDiff = glm::length(v1 - v2);
            float freedEnergy = ((m1 * m2) / (2*(m1 + m2))) * (speedDiff * speedDiff) * (1.0f - m_elasticity * m_elasticity);

            if (voxelCollision.a().worldObject()->spawnState() != SpawnState::RemovalScheduled) {
                m_damageImpactAccumulator.parse(DamageImpact(voxelCollision.a().worldObject(),
                                                             voxelCollision.a().voxel(),
                                                             glm::normalize(v2 - v1) * (freedEnergy/2),
                                                             voxelCollision.b().worldObject()->collisionFieldOfDamage()));
            }
            if (voxelCollision.b().worldObject()->spawnState() != SpawnState::RemovalScheduled) {
                m_damageImpactAccumulator.parse(DamageImpact(voxelCollision.b().worldObject(),
                                                             voxelCollision.b().voxel(),
                                                             glm::normalize(v1 - v2) * (freedEnergy/2),
                                                             voxelCollision.a().worldObject()->collisionFieldOfDamage()));
            }
        }
    }
}

void DamageImpactGenerator::parse(std::list<DamageImpact>& damageImpacts) {
    for (DamageImpact& damageImpact : damageImpacts) {
          m_damageImpactAccumulator.parse(damageImpact);
    }
}

std::list<DamageImpact>& DamageImpactGenerator::damageImpacts() {
    return m_damageImpactAccumulator.accumulatables();
}

