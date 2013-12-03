#include "damageforwarder.h"

#include <cmath>
#include <algorithm>
#include <glm/glm.hpp>

#include "voxel/voxelcluster.h"
#include "collision/voxeltreenode.h"

#include "voxel/voxelneighbourhelper.h"
#include "utils/tostring.h"

#include "worldobject/worldobject.h"



void DamageForwarder::forwardDamageImpacts(std::list<Impact> &dampedDeadlyImpacts) {
    std::list<Impact> forwardedDamageImpacts;

    ImpactAccumulator::clear();

    for(Impact &dampedDeadlyImpact : dampedDeadlyImpacts) {
        Voxel *deadVoxel = dampedDeadlyImpact.voxel();

        m_currentWorldObject = dampedDeadlyImpact.worldObject();
        std::list<Voxel*> neighbours = VoxelNeighbourHelper(m_currentWorldObject, deadVoxel).neighbours();
        glm::vec3 localImpactVec = glm::inverse(m_currentWorldObject->transform().orientation()) * dampedDeadlyImpact.vec();

        for(Voxel *neighbour : neighbours) {
            glm::vec3 voxelVec = static_cast<glm::vec3>(neighbour->gridCell() - deadVoxel->gridCell());
            float dotProduct = glm::dot(glm::normalize(localImpactVec), glm::normalize(voxelVec));

            if(dotProduct >= 0.0f) {
                Impact forwarded(m_currentWorldObject, neighbour, localImpactVec * forwardFactor(dotProduct));
                forwardedDamageImpacts.push_back(forwarded);
            }
        }
    }

    ImpactAccumulator::parse(forwardedDamageImpacts);
}

void DamageForwarder::dontForwardTo(std::list<Voxel*> &deadVoxels) {
    ImpactAccumulator::dontImpact(deadVoxels);
}

std::list<Impact> DamageForwarder::forwardedDamageImpacts() {
    return ImpactAccumulator::impacts();
}

float DamageForwarder::forwardFactor(float dotProduct) {
    return (M_PI/2 - std::acos(dotProduct)) / (M_PI/2);
}

