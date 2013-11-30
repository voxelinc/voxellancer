#include "damager.h"

#include "impact.h"


void Damager::applyDamages(std::list<Impact> &impacts) {
    m_deadlyImpacts.clear();
    m_modifiedWorldObjects.clear();

    for(Impact &impact : impacts) {
        Voxel *voxel = impact.voxel();

        voxel->applyDamage(damageOfImpact(impact));
        if(voxel->hp() <= 0) {
            m_deadlyImpacts.push_back(impact);
            m_modifiedWorldObjects.insert(voxel->voxelCluster());
        }
    }
}

std::list<Impact> &Damager::deadlyVoxelImpacts() {
    return m_deadlyImpacts;
}

std::list<WorldObject*> &Damager::modifiedVoxelClusters() {
    return m_modifiedWorldObjects;
}

float Damager::damageOfImpact(const Impact &impact) const {
    return glm::length(impact.vec());
}

