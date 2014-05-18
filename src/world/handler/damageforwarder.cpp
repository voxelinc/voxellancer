#include "damageforwarder.h"

#include <cmath>
#include <algorithm>
#include <glm/glm.hpp>

#include "utils/safenormalize.h"

#include "voxel/voxelcluster.h"
#include "voxel/voxeltreenode.h"

#include "voxel/voxelneighbourhelper.h"

#include "worldobject/worldobject.h"
#include "voxel/voxel.h"



void DamageForwarder::forwardDamageImpacts(std::list<DamageImpact> &dampedDeadlyDamageImpacts) {
    m_damageImpactAccumulator.clear();

    for(DamageImpact &dampedDeadlyDamageImpact : dampedDeadlyDamageImpacts) {
        Voxel *deadVoxel = dampedDeadlyDamageImpact.voxel();

        m_currentWorldObject = dampedDeadlyDamageImpact.worldObject();
        VoxelNeighbourHelper nHelper(m_currentWorldObject, true);
        const std::vector<Voxel*>& neighbours = nHelper.neighbours(deadVoxel);

        for(Voxel *neighbour : neighbours) {
            glm::vec3 voxelVec = glm::normalize(static_cast<glm::vec3>(neighbour->gridCell() - deadVoxel->gridCell()));
            glm::vec3 damageImpactVec = glm::normalize(glm::inverse(m_currentWorldObject->transform().orientation()) * dampedDeadlyDamageImpact.damageVec());

            float distanceFactor = 1.0f;
            if ((voxelVec.x != 0 && voxelVec.y != 0) || (voxelVec.x != 0 && voxelVec.z != 0) || (voxelVec.y != 0 && voxelVec.z != 0)) {
                // diagonals get less damage
                distanceFactor = 0.5f;
            }

            float dotProduct = glm::dot(damageImpactVec, voxelVec);
            glm::vec3 forwardedDamage = dampedDeadlyDamageImpact.damageVec() * forwardFactor(dotProduct, dampedDeadlyDamageImpact.fieldOfDamage(), neighbours.size());
            glm::vec3 createdDamage = voxelVec * deadVoxel->damageForwardingDestructionDamage();

            DamageImpact forwarded(m_currentWorldObject,
                                    neighbour,
                                    distanceFactor * (forwardedDamage + createdDamage),
                                    dampedDeadlyDamageImpact.fieldOfDamage());
            m_damageImpactAccumulator.parse(forwarded);
        }
    }
}

void DamageForwarder::dontForwardTo(std::list<Voxel*> &deadVoxels) {
    m_damageImpactAccumulator.dontAffect(deadVoxels);
}

std::list<DamageImpact> DamageForwarder::forwardedDamageImpacts() {
    return m_damageImpactAccumulator.accumulatables();
}

float DamageForwarder::forwardFactor(float dotProduct, float fieldOfDamage, int neighbours) {
    return glm::max(0.0f, (fieldOfDamage - std::acos(dotProduct)) / fieldOfDamage) / neighbours;
}

