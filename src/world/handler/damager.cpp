#include "damager.h"

#include <set>

#include <glow/logging.h>

#include "equipment/shield.h"
#include "equipment/shieldslot.h"

#include "voxel/voxel.h"

#include "worldobject/ship.h"
#include "worldobject/worldobject.h"
#include "worldobject/worldobjectcomponents.h"

#include "world/world.h"
#include "world/helper/damageimpact.h"

#include "player.h"


Damager::Damager() :
    m_playerShipUndestroyable("general.playerShipUndestroyable")
{
}

void Damager::applyDamages(std::list<DamageImpact> &damageImpacts) {
    m_dampedDeadlyDamageImpacts.clear();
    m_deadlyDamageImpacts.clear();
    m_deadVoxels.clear();

    for(DamageImpact &damageImpact : damageImpacts) {
        if (m_playerShipUndestroyable && World::instance()->player().ship() == damageImpact.worldObject()) {
            continue;
        }

        applyShields(damageImpact);
        if(damageImpact.damage() == 0) {
            continue;
        }

        Voxel *voxel = damageImpact.voxel();

        float hpBeforeDamage = voxel->hp();
        voxel->applyDamage(damageImpact.damage());

        if(voxel->hp() <= 0) {
            m_dampedDeadlyDamageImpacts.push_back(dampDamageImpact(damageImpact, damageImpact.damage() - hpBeforeDamage));
            m_deadlyDamageImpacts.push_back(damageImpact);
            m_deadVoxels.push_back(voxel);

            auto i = m_worldObjectModificationMap.find(damageImpact.worldObject());
            if(i == m_worldObjectModificationMap.end()) {
                WorldObjectModification modification(damageImpact.worldObject());
                modification.removedVoxel(voxel->cell());
                m_worldObjectModificationMap.insert(std::pair<WorldObject*, WorldObjectModification>(damageImpact.worldObject(), modification));
            } else {
                i->second.removedVoxel(voxel->cell());
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
    return DamageImpact(undamped.worldObject(), undamped.voxel(), glm::normalize(undamped.damageVec()) * factor, undamped.fieldOfDamage());
}

void Damager::reset() {
    m_worldObjectModificationMap.clear();
}

void Damager::applyShields(DamageImpact& damageImpact) {
    damageImpact.setDamage(damageImpact.worldObject()->components().compensateDamage(damageImpact.damage()));
}

