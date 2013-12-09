#pragma once

#include <map>
#include <list>

#include "world/helper/impact.h"
#include "world/helper/worldobjectmodification.h"


class WorldObject;

class Damager
{
public:
    void applyDamages(std::list<Impact> &impacts);

    std::list<Impact> &dampedDeadlyImpacts();
    std::list<Impact> &deadlyImpacts();
    std::list<Voxel*> &deadVoxels();
    std::list<WorldObjectModification> worldObjectModifications();


protected:
    std::list<Impact> m_dampedDeadlyImpacts;
    std::list<Impact> m_deadlyImpacts;
    std::list<Voxel*> m_deadVoxels;
    std::map<WorldObject*, WorldObjectModification> m_worldObjectModificationMap;

    float damageOfImpact(const Impact &impact) const;
    Impact dampImpact(Impact &undamped, float factor);
};

