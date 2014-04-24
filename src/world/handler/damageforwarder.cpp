#include "damageforwarder.h"

#include <cmath>
#include <algorithm>
#include <glm/glm.hpp>

#include "voxel/voxelcluster.h"
#include "voxel/voxeltreenode.h"

#include "voxel/voxelneighbourhelper.h"
#include "utils/tostring.h"

#include "worldobject/worldobject.h"
#include "voxel/voxel.h"



void DamageForwarder::forwardDamageImpacts(std::list<DamageImpact> &dampedDeadlyDamageImpacts) {
    m_damageImpactAccumulator.clear();

    for(DamageImpact &dampedDeadlyDamageImpact : dampedDeadlyDamageImpacts) {
        Voxel *deadVoxel = dampedDeadlyDamageImpact.voxel();

        m_currentWorldObject = dampedDeadlyDamageImpact.worldObject();
        VoxelNeighbourHelper nHelper(m_currentWorldObject, true);
        const std::vector<Voxel*> neighbours = nHelper.neighbours(deadVoxel);


        std::list<std::pair<Voxel*, glm::vec3>> forwardedPerNeighbour;
        float totalForwardedDamage = 0.0f;

        for(Voxel* neighbour : neighbours) {
            glm::vec3 voxelVec = glm::normalize(static_cast<glm::vec3>(neighbour->gridCell() - deadVoxel->gridCell()));
            glm::vec3 damageImpactVec = glm::normalize(glm::inverse(m_currentWorldObject->transform().orientation()) * dampedDeadlyDamageImpact.damageVec());

            // diagonals get less damage
            float distanceFactor = 1.0f;
            if (voxelVec.x + voxelVec.y + voxelVec.z > 1.0f) {
                distanceFactor = 0.7f;
            }

            float dotProduct = glm::dot(damageImpactVec, voxelVec);
            glm::vec3 forwardedDamage = dampedDeadlyDamageImpact.damageVec() * forwardFactor(dotProduct, dampedDeadlyDamageImpact.fieldOfDamage(), neighbours.size());
            glm::vec3 createdDamage = voxelVec * deadVoxel->damageForwardingDestructionDamage();

            glm::vec3 actualForwardedDamage = distanceFactor * (forwardedDamage + createdDamage);
            totalForwardedDamage += glm::length(actualForwardedDamage);

            forwardedPerNeighbour.push_back(std::make_pair(neighbour, actualForwardedDamage));
        }

        if (forwardedPerNeighbour.empty() || totalForwardedDamage == 0.0f) {
            continue;
        }

        // Hacked fix to prevent damage from being lost during forwarding
        float losslessFactor = (dampedDeadlyDamageImpact.damage() / totalForwardedDamage) * (forwardedPerNeighbour.size() / 26.0f);

        for (auto& pair : forwardedPerNeighbour) {
            DamageImpact forwarded( m_currentWorldObject,
                                    pair.first,
                                    pair.second * losslessFactor,
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

