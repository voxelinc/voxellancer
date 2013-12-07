#pragma once

#include <map>
#include <list>


class WorldObject;
class Impact;

class ImpactResolver
{
public:
    void alterVelocities(std::list<Impact> &allImpacts);


protected:
    std::map<WorldObject*, std::list<Impact>> m_impactsPerWordObject;

    void alterVelocity(WorldObject* worldObject, const Impact& impact);
    void calculateImpactsPerWorldObject(const std::list<Impact> &allImpacts);
};

