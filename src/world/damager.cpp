#include "damager.h"


void Damager::applyDamages(std::list<VoxelImpact> &voxelImpacts) {
    m_deadlyVoxelImpacts.clear();
    m_modifiedVoxelClusters.clear();
}

std::list<VoxelImpact> &Damager::deadlyVoxelImpacts() {
    return m_deadlyVoxelImpacts;
}

std::list<VoxelCluster*> &Damager::modifiedVoxelClusters() {
    return m_modifiedVoxelClusters;
}
