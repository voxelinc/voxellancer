#include "impactaccumulator.h"


void ImpactAccumulator::clear() {
    m_impacts.clear();
}

void ImpactAccumulator::parse(const std::list<Impact> &collisions) {
    m_impacts.insert(m_impacts.end(), collisions.begin(), collisions.end());
}

//void ImpactAccumulator::parse(const std::list<PhysicalVoxelImpact> &physicalVoxelImpact) {
//
//}

//std::list<PhysicalVoxelClusterImpact> &ImpactAccumulator::clusterImpacts() {
//    return m_clusterImpacts;
//}

std::list<Impact> &ImpactAccumulator::impacts() {
    return m_impacts;
}
