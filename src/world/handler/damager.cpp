#include "damager.h"
#include <glow/logging.h>

#include "world/helper/impact.h"
#include "voxel/voxel.h"
#include "utils/tostring.h"


void Damager::applyDamages(std::list<Impact> &impacts) {
    m_dampedDeadlyImpacts.clear();
    m_deadlyImpacts.clear();
    m_modifiedWorldObjects.clear();
    m_deadVoxels.clear();

    for(Impact &impact : impacts) {
        Voxel *voxel = impact.voxel();

        float hpBeforeDamage = voxel->hp();
        float damage = damageOfImpact(impact);

        voxel->applyDamage(damage);
        if(voxel->hp() <= 0) {
            m_dampedDeadlyImpacts.push_back(dampImpact(impact, damage - hpBeforeDamage));
            m_deadlyImpacts.push_back(impact);
            m_deadVoxels.push_back(voxel);
            m_modifiedWorldObjects.insert(impact.worldObject());
        }
    }
}

std::list<Impact> &Damager::dampedDeadlyImpacts() {
    return m_dampedDeadlyImpacts;
}

std::list<Impact> &Damager::deadlyImpacts() {
    return m_deadlyImpacts;
}

std::list<Voxel*> &Damager::deadVoxels() {
    return m_deadVoxels;
}

std::set<WorldObject*> &Damager::modifiedWorldObjects() {
    return m_modifiedWorldObjects;
}

float Damager::damageOfImpact(const Impact &impact) const {
    return glm::length(impact.vec());
}

Impact Damager::dampImpact(Impact &undamped, float factor) {
    return Impact(undamped.worldObject(), undamped.voxel(), glm::normalize(undamped.vec()) * factor);
}
