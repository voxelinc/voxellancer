#pragma once

#include <set>
#include <list>

#include "impact.h"


class WorldObject;

class Damager
{
public:
    void applyDamages(std::list<Impact> &impacts);

    std::list<Impact> &deadlyImpact();
    std::set<WorldObject*> &modifiedWorldObjects();


protected:
    std::list<Impact> m_deadlyImpacts;
    std::set<WorldObject*> m_modifiedWorldObjects;

    float damageOfImpact(const Impact &impact) const;
};

