#include "damager.h"

#include <set>
#include <iostream>
#include <glow/logging.h>

#include "world/helper/impact.h"
#include "voxel/voxel.h"
#include "utils/tostring.h"


void Damager::applyDamages(std::list<Impact> &impacts) {
    m_dampedDeadlyImpacts.clear();
    m_deadlyImpacts.clear();
    m_worldObjectModificationMap.clear();
    m_deadVoxels.clear();

    for(Impact &impact : impacts) {
        Voxel *voxel = impact.voxel();

        float hpBeforeDamage = voxel->hp();
        float damage = damageOfImpact(impact);
        voxel->applyDamage(damage);
        if(voxel->hp() <= 0) {
        std::cout << impact.worldObject() << " " << toString(impact.vec()) << " => " << toString(dampImpact(impact, damage - hpBeforeDamage).vec()) << std::endl;
            m_dampedDeadlyImpacts.push_back(dampImpact(impact, damage - hpBeforeDamage));
            m_deadlyImpacts.push_back(impact);
            m_deadVoxels.push_back(voxel);

            auto i = m_worldObjectModificationMap.find(impact.worldObject());
            if(i == m_worldObjectModificationMap.end()) {
                WorldObjectModification modification(impact.worldObject());
                modification.cellCleared(voxel->gridCell());
                m_worldObjectModificationMap.insert(std::pair<WorldObject*, WorldObjectModification>(impact.worldObject(), modification));
            }
            else {
                i->second.cellCleared(voxel->gridCell());
            }
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

std::list<WorldObjectModification> Damager::worldObjectModifications() {
    std::list<WorldObjectModification> result;

    for(auto& pair : m_worldObjectModificationMap) {
        result.push_back(pair.second);
    }
    return result;
}

float Damager::damageOfImpact(const Impact &impact) const {
    return glm::length(impact.vec());
}

Impact Damager::dampImpact(Impact &undamped, float factor) {
    return Impact(undamped.worldObject(), undamped.voxel(), glm::normalize(undamped.vec()) * factor);
}
