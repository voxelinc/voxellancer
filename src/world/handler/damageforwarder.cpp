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

    for(DamageImpact& damageImpact : dampedDeadlyDamageImpacts) {
        forward(damageImpact);
    }
}

void DamageForwarder::dontForwardTo(std::list<Voxel*> &deadVoxels) {
    m_damageImpactAccumulator.dontAffect(deadVoxels);
}

std::list<DamageImpact> DamageForwarder::forwardedDamageImpacts() {
    return m_damageImpactAccumulator.accumulatables();
}

void DamageForwarder::forward(DamageImpact& damageImpact) {
    m_currentDeadVoxel = damageImpact.voxel();
    m_currentWorldObject = damageImpact.worldObject();
    m_currentDamageVec = damageImpact.damageVec();
    m_currentFieldOfDamage = damageImpact.fieldOfDamage();

    std::vector<Voxel*> neighbours = VoxelNeighbourHelper(m_currentWorldObject, true).neighbours(deadVoxel);

    std::list<std::pair<Voxel*, glm::vec3>> forwardedPerNeighbour;
    float totalForwardedDamage = 0.0f;

    for(Voxel* neighbour : neighbours) {
        glm::vec3 damageVec = calculateForwardingToVoxel(neighbour)

        totalForwardedDamage += glm::length(damageVec);

        forwardedPerNeighbour.push_back(std::make_pair(neighbour, damageVec));
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

float DamageForwarder::forwardFactor(float dotProduct, float fieldOfDamage, int neighbours) {
    return glm::max(0.0f, (fieldOfDamage - std::acos(dotProduct)) / fieldOfDamage) / neighbours;
}

glm::vec3 DamageForwarder::calculateForwardingToVoxel(Voxel* voxel) {
    glm::vec3 voxelVec = glm::normalize(static_cast<glm::vec3>(voxel->gridCell() - m_currentDeadVoxel->gridCell()));
    glm::vec3 damageImpactVec = glm::normalize(glm::inverse(m_currentWorldObject->transform().orientation()) * m_currentDamageVec);

    // diagonals get less damage
    float distanceFactor = 1.0f;
    if (voxelVec.x + voxelVec.y + voxelVec.z > 1.0f) {
        distanceFactor = 0.71f;
    }

    float dotProduct = glm::dot(damageImpactVec, voxelVec);
    glm::vec3 forwardedDamage = m_currentDamageVec * forwardFactor(dotProduct, m_currentFieldOfDamage, neighbours.size());
    glm::vec3 createdDamage = voxelVec * deadVoxel->damageForwardingDestructionDamage();

    return distanceFactor * (forwardedDamage + createdDamage);
}
