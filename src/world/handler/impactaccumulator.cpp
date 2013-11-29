#include "impactaccumulator.h"

#include "physics/physicalvoxelimpact.h"


void ImpactAccumulator::clear() {
    m_clusterImpacts.clear();
}

void ImpactAccumulator::parse(const std::list<Collision> &collisions) {

}

void ImpactAccumulator::parse(const std::list<PhysicalVoxelImpact> &physicalVoxelImpact) {

}

//std::list<PhysicalVoxelClusterImpact> &ImpactAccumulator::clusterImpacts() {
//    return m_clusterImpacts;
//}

std::list<PhysicalVoxelImpact> &ImpactAccumulator::physicalVoxelImpacts() {
    return m_physicalVoxelImpacts;
}
