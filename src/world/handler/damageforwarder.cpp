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

        for(Voxel *neighbour : neighbours) {
            glm::vec3 voxelVec = static_cast<glm::vec3>(neighbour->gridCell() - deadVoxel->gridCell());
            float dotProduct = glm::dot(glm::normalize(dampedDeadlyImpact.vec()), glm::normalize(voxelVec));

            if(dotProduct >= 0.0f) {
                Impact forwarded(m_currentWorldObject, neighbour, dampedDeadlyImpact.vec() * forwardFactor(dotProduct));
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
    return (glm::half_pi<float>() - std::acos(dotProduct)) / glm::half_pi<float>();
}

