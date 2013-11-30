#include "impactaccumulator.h"


void ImpactAccumulator::clear() {
    m_impacts.clear();
}

void ImpactAccumulator::parse(const std::list<Collision> &collisions) {

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
