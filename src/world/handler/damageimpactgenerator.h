#pragma once

#include <list>

#include "collision/worldobjectcollision.h"

#include "world/helper/impact.h"

#include "impactaccumulator.h"


class DamageImpactGenerator {
public:
    void parse(std::list<WorldObjectCollision>& worldObjectCollisions);

    std::list<Impact>& damageImpacts();


protected:
    ImpactAccumulator m_impactAccumulator;
};
