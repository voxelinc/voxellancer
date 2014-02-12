#pragma once

#include <list>

#include "collision/worldobjectcollision.h"
#include "world/helper/damageimpact.h"
#include "world/helper/voxelaccumulator.h"


class DamageImpactGenerator {
public:
    void parse(std::list<WorldObjectCollision>& worldObjectCollisions);

    std::list<DamageImpact>& damageImpacts();


protected:
    VoxelAccumulator<DamageImpact> m_damageImpactAccumulator;
};
