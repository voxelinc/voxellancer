#include "damageforwarder.h"

#include <algorithm>
#include <glm/glm.hpp>

#include "voxel/voxelcluster.h"
#include "collision/voxeltreenode.h"

#include "voxel/voxelneighbourhelper.h"
#include "utils/tostring.h"

#include "worldobject/worldobject.h"



void DamageForwarder::forwardDamage(std::list<Impact> &dampedDeadlyImpacts) {
    std::list<Impact> forwardedDamageImpacts;

    ImpactAccumulator::clear();

    for(Impact &dampedDeadlyImpact : dampedDeadlyImpacts) {
        std::cout << "Forwarding impact on " << dampedDeadlyImpact.worldObject() << std::endl;
        Voxel *deadVoxel = dampedDeadlyImpact.voxel();

        m_currentWorldObject = dampedDeadlyImpact.worldObject();
        std::list<Voxel*> neighbours = VoxelNeighbourHelper(m_currentWorldObject, deadVoxel).neighbours();
            std::cout << "  has " << neighbours.size() << " possibly affected neighbours" << std::endl;

        std::cout << "Vec " << toString(dampedDeadlyImpact.vec()) << " => ";
        glm::vec3 localImpactVec = glm::inverse(m_currentWorldObject->transform().orientation()) * dampedDeadlyImpact.vec();
        std::cout << toString(localImpactVec) << std::endl;


        for(Voxel *neighbour : neighbours) {
            glm::vec3 voxelVec = static_cast<glm::vec3>(neighbour->gridCell() - deadVoxel->gridCell());
            float dotProduct = glm::dot(glm::normalize(localImpactVec), glm::normalize(voxelVec));
            std::cout << "Dot product is " << toString(glm::normalize(localImpactVec)) << " * " << toString(glm::normalize(voxelVec)) << "=>"<< dotProduct << std::endl;
            if(dotProduct >= 0.0f) {
                Impact forwarded(m_currentWorldObject, neighbour, localImpactVec * dotProduct);
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

std::list<Voxel*> DamageForwarder::getNeighbours(Voxel *voxel) {
    std::list<Voxel*> neighbours;

    m_currentNeighbours = &neighbours;
    m_currentGridCell = voxel->gridCell();

    considerNeighbour(glm::ivec3(-1, 0, 0));
    considerNeighbour(glm::ivec3(+1, 0, 0));
    considerNeighbour(glm::ivec3(0, -1, 0));
    considerNeighbour(glm::ivec3(0, +1, 0));
    considerNeighbour(glm::ivec3(0, 0, -1));
    considerNeighbour(glm::ivec3(0, 0, +1));

    return neighbours;
}

void DamageForwarder::considerNeighbour(const glm::ivec3 &cellDelta) {
    Voxel *neighbour = m_currentWorldObject->voxel(m_currentGridCell + cellDelta);
    if(neighbour == nullptr) {
        return;
    }

    m_currentNeighbours->push_back(neighbour);
}

