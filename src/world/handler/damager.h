#pragma once

#include <set>
#include <list>

#include "world/helper/impact.h"


class WorldObject;

class Damager
{
public:
    void applyDamages(std::list<Impact> &impacts);

    std::list<Impact> &dampedDeadlyImpacts();
    std::list<Impact> &deadlyImpacts();
    std::list<Voxel*> &deadVoxels();
    std::set<WorldObject*> &modifiedWorldObjects();


protected:
    std::list<Impact> m_dampedDeadlyImpacts;
    std::list<Impact> m_deadlyImpacts;
    std::list<Voxel*> m_deadVoxels;
    std::set<WorldObject*> m_modifiedWorldObjects;

    float damageOfImpact(const Impact &impact) const;
    Impact dampImpact(Impact &undamped, float factor);
};
