#include "damager.h"

#include "voxel/voxel.h"


void Damager::applyDamages(std::list<VoxelImpact> &voxelImpacts) {
    m_deadlyVoxelImpacts.clear();
    m_modifiedVoxelClusters.clear();

    for(VoxelImpact &voxelImpact : voxelImpacts) {
        Voxel *voxel = voxelImpact.voxel();

        voxel->applyDamage(damageOfImpact(voxelImpact.impact()));
        if(voxel->hp() <= 0) {
            m_deadlyVoxelImpacts.push_back(voxelImpact);
            m_modifiedVoxelClusters.insert(voxel->voxelCluster());
        }
    }
}

std::list<VoxelImpact> &Damager::deadlyVoxelImpacts() {
    return m_deadlyVoxelImpacts;
}

std::list<WorldObject*> &Damager::modifiedVoxelClusters() {
    return m_modifiedVoxelClusters;
}

float Damager::damageOfImpact(const Impact &impact) const {
    return glm::length(impact.vec3());
}

