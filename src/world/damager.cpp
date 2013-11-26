#include "damager.h"


void Damager::applyDamages(std::list<VoxelImpact> &voxelImpacts) {
    m_dampedDeadlyVoxelImpacts.clear();
    m_deadVoxels.clear();
    m_modifiedVoxelClusters.clear();

    for(VoxelImpact &voxelImpact : voxelImpacts) {
        Voxel *voxel = voxelImpact.voxel();

        float hpBeforeDamage = voxel->hp();
        float damage = damageOfImpact(voxelImpact.impact());

        voxel->applyDamage(damage);
        if(voxel->hp() <= 0) {
            m_dampedDeadlyVoxelImpacts.push_back(dampVoxelImpact(voxelImpact, hpBeforeDamage / damage));
            m_deadVoxels.push_back(voxel);
            m_modifiedVoxelClusters.insert(voxel->voxelCluster());
        }
    }
}

std::list<VoxelImpact> &Damager::dampedDeadlyVoxelImpacts() {
    return m_dampedDeadlyVoxelImpacts;
}

std::list<Voxel*> &Damager::deadVoxels() {
    return m_deadVoxels;
}

std::set<VoxelCluster*> &Damager::modifiedVoxelClusters() {
    return m_modifiedVoxelClusters;
}

float Damager::damageOfImpact(const Impact &impact) const {
    return glm::length(impact.vec3());
}

VoxelImpact Damager::dampVoxelImpact(VoxelImpact &undamped, float factor) {
    VoxelImpact damped(undamped.voxel());

    damped.setImpact(Impact(undamped.impact().vec3() * factor));

    return damped;
}

