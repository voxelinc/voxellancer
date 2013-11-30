#include "damager.h"

#include "impact.h"


void Damager::applyDamages(std::list<Impact> &impacts) {
    m_dampedDeadlyImpacts.clear();
    m_deadlyImpacts.clear();
    m_modifiedWorldObjects.clear();

    for(Impact &impact : impacts) {
        Voxel *voxel = impact.voxel();

        float hpBeforeDamage = voxel->hp();
        float damage = damageOfImpact(impact);

        voxel->applyDamage(damage);
        if(voxel->hp() <= 0) {
            m_dampedDeadlyImpacts.push_back(dampImpact(impact, hpBeforeDamage / damage));
            m_deadlyImpacts.push_back(impact);
            m_modifiedWorldObjects.insert(voxel->voxelCluster());
        }
    }
}

std::list<Impact> &Damager::dampedDeadlyImpacts() {
    return m_dampedDeadlyImpacts;
}

std::list<Impact> &Damager::deadlyImpacts() {
    return m_deadlyImpacts;
}

std::set<WorldObject*> &Damager::modifiedWorldObjects() {
    return m_modifiedWorldObjects;
}

float Damager::damageOfImpact(const Impact &impact) const {
    return glm::length(impact.vec3());
}

Impact Damager::dampImpact(Impact &undamped, float factor) {
    return Impact(undamped.impact().vec3() * factor);
}
