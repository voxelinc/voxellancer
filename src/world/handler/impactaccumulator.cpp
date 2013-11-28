#include "impactaccumulator.h"

void ImpactAccumulator::clear() {
    m_clusterImpacts.clear();
}

void ImpactAccumulator::parse(const std::list<Collision> &collisions) {

}

void ImpactAccumulator::parse(const std::list<VoxelImpact> &voxelImpacts) {

}

std::list<VoxelClusterImpact> &ImpactAccumulator::clusterImpacts() {
    return m_clusterImpacts;
}

std::list<VoxelImpact> &ImpactAccumulator::voxelImpacts() {
    return m_voxelImpacts;
}
