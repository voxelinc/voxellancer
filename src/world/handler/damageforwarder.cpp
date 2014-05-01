#include "damageforwarder.h"

#include <cmath>
#include <algorithm>

#include <glm/glm.hpp>

#include <glow/logging.h>

#include "voxel/voxelcluster.h"
#include "voxel/voxeltreenode.h"

#include "voxel/voxelneighbourhelper.h"

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

    std::vector<Voxel*> neighbours = VoxelNeighbourHelper(m_currentWorldObject, true).neighbours(m_currentDeadVoxel);

    std::list<std::pair<Voxel*, glm::vec3>> forwardedPerNeighbour;
    float totalForwardedDamage = 0.0f;

    for(Voxel* neighbour : neighbours) {
        glm::vec3 damageVec = calculateForwardingToVoxel(neighbour);
        totalForwardedDamage += glm::length(damageVec);

        forwardedPerNeighbour.push_back(std::make_pair(neighbour, damageVec));
    }

    if (forwardedPerNeighbour.empty() || totalForwardedDamage == 0.0f) {
        return;
    }

    /* Hacked fix to prevent damage from being lost during forwarding
        The former algorithm did a nice job distributing damage relatively. That means voxels in the direction
        of the damageVec received more damage, incorporated nicely with the fieldOfDamage.
        HOWEVER, damage energy is lost during the distribution to the surrounding gridCells.
        The calculation and application of the losslessFactor compensates this by virtually determining how much
        damage was relatively lost compared to the original damage and multiplicates that to every forwarding
    */
    float losslessFactor = ((damageImpact.damage() + m_currentDeadVoxel->damageForwardingDestructionDamage())  / totalForwardedDamage) * (forwardedPerNeighbour.size() / 26.0f);

    for (auto& pair : forwardedPerNeighbour) {
        DamageImpact forwarded( m_currentWorldObject,
                                pair.first,
                                pair.second * losslessFactor,
                                damageImpact.fieldOfDamage());
        m_damageImpactAccumulator.parse(forwarded);
    }
}

float DamageForwarder::forwardFactor(float dotProduct, float fieldOfDamage) {
    return glm::max(0.0f, (fieldOfDamage - std::acos(dotProduct)) / fieldOfDamage);
}

glm::vec3 DamageForwarder::calculateForwardingToVoxel(Voxel* voxel) {
    glm::ivec3 gridStep = voxel->gridCell() - m_currentDeadVoxel->gridCell();
    glm::vec3 damageImpactVec = glm::normalize(glm::inverse(m_currentWorldObject->transform().orientation()) * m_currentDamageVec);

    float distanceFactor = calculateDistanceFactor(gridStep);
    float dotProduct = glm::dot(damageImpactVec, glm::normalize(glm::vec3(gridStep)));

    glm::vec3 forwardedDamage = m_currentDamageVec * forwardFactor(dotProduct, m_currentFieldOfDamage);
    glm::vec3 createdDamage = glm::vec3(gridStep) * m_currentDeadVoxel->damageForwardingDestructionDamage();

    return distanceFactor * (forwardedDamage + createdDamage);
}

float DamageForwarder::calculateDistanceFactor(const glm::ivec3& gridStep) const {
    glm::ivec3 absStep = glm::abs(gridStep);

    int gridSteps = absStep.x + absStep.y + absStep.z;
    switch (gridSteps) {
        case 1: return 1.00f;
        case 2: return 0.70f;
        case 3: return 0.58f;
        case 4: assert(false); return 0.0f;
    }
}

