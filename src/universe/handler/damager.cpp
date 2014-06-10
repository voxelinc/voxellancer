#include "damager.h"

#include <set>
#include <glow/logging.h>

#include "voxel/voxel.h"

#include "worldobject/worldobject.h"
#include "worldobject/ship.h"

#include "universe/helper/damageimpact.h"

#include "player.h"


Damager::Damager() = default;

void Damager::applyDamages(std::list<DamageImpact>& damageImpacts) {
    m_dampedDeadlyDamageImpacts.clear();
    m_deadlyDamageImpacts.clear();
    m_deadVoxels.clear();

    for(DamageImpact& damageImpact : damageImpacts) {
        Voxel* voxel = damageImpact.voxel();
        WorldObject* worldObject = damageImpact.worldObject();

        if (worldObject->invincible()) {
            continue;
        }

        float hpBeforeDamage = voxel->hp();
        voxel->applyDamage(damageImpact.damage());

        if(voxel->hp() <= 0) {
            m_dampedDeadlyDamageImpacts.push_back(dampDamageImpact(damageImpact, damageImpact.damage() - hpBeforeDamage));
            m_deadlyDamageImpacts.push_back(damageImpact);
            m_deadVoxels.push_back(voxel);

            auto i = m_worldObjectModificationMap.find(worldObject);
            if(i == m_worldObjectModificationMap.end()) {
                WorldObjectModification modification(worldObject);
                modification.removedVoxel(voxel->gridCell());
                m_worldObjectModificationMap.insert(std::pair<WorldObject*, WorldObjectModification>(worldObject, modification));
            } else {
                i->second.removedVoxel(voxel->gridCell());
            }
        }
    }
}

std::list<DamageImpact> &Damager::dampedDeadlyDamageImpacts() {
    return m_dampedDeadlyDamageImpacts;
}

std::list<DamageImpact> &Damager::deadlyDamageImpacts() {
    return m_deadlyDamageImpacts;
}

std::list<Voxel*> &Damager::deadVoxels() {
    return m_deadVoxels;
}

std::list<WorldObjectModification>& Damager::worldObjectModifications() {
    m_worldObjectModifications.clear();

    for(auto& pair : m_worldObjectModificationMap) {
        m_worldObjectModifications.push_back(pair.second);
    }
    return m_worldObjectModifications;
}

DamageImpact Damager::dampDamageImpact(DamageImpact &undamped, float factor) {
    return DamageImpact(undamped.worldObject(), undamped.voxel(), undamped.damageVec() * factor, undamped.fieldOfDamage());
}

void Damager::reset() {
    m_worldObjectModificationMap.clear();
}

