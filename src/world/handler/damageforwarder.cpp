#include "damageforwarder.h"

#include <cmath>
#include <algorithm>

#include <glm/glm.hpp>

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

    // Hacked fix to prevent damage from being lost during forwarding
    float losslessFactor = (damageImpact.damage() / totalForwardedDamage) * (forwardedPerNeighbour.size() / 26.0f);

    std::cout << "LosslessFactor is " <<  damageImpact.damage() << " " << totalForwardedDamage << " " <<forwardedPerNeighbour.size() << std::endl;

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

    // diagonals get less damage
    float distanceFactor;
    int gridSteps = gridStep.x + gridStep.y + gridStep.z;
    switch (gridSteps) {
        case 1: distanceFactor = 1.00f; break;
        case 2: distanceFactor = 0.70f; break;
        case 3: distanceFactor = 0.58f; break;
        case 4: assert(false); break;
    }

    float dotProduct = glm::dot(damageImpactVec, glm::vec3(gridStep));
    glm::vec3 forwardedDamage = m_currentDamageVec * forwardFactor(dotProduct, m_currentFieldOfDamage);
    glm::vec3 createdDamage = glm::vec3(gridStep) * m_currentDeadVoxel->damageForwardingDestructionDamage();

    return distanceFactor * (forwardedDamage + createdDamage);
}
