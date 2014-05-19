#pragma once

#include <map>
#include <list>

#include "universe/helper/damageimpact.h"
#include "universe/helper/worldobjectmodification.h"

#include "property/property.h"


class WorldObject;

class Damager {
public:
    Damager();

    void applyDamages(std::list<DamageImpact> &damageImpacts);
    void reset();

    std::list<DamageImpact> &dampedDeadlyDamageImpacts();
    std::list<DamageImpact> &deadlyDamageImpacts();
    std::list<Voxel*> &deadVoxels();
    std::list<WorldObjectModification>& worldObjectModifications();


protected:
    std::list<DamageImpact> m_dampedDeadlyDamageImpacts;
    std::list<DamageImpact> m_deadlyDamageImpacts;
    std::list<Voxel*> m_deadVoxels;
    std::map<WorldObject*, WorldObjectModification> m_worldObjectModificationMap;
    std::list<WorldObjectModification> m_worldObjectModifications;

    DamageImpact dampDamageImpact(DamageImpact &undamped, float factor);
};

