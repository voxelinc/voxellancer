#pragma once

#include <list>

#include "collision/worldobjectcollision.h"

#include "world/helper/impact.h"


class ElasticImpactGenerator {
public:
    void parse(std::list<WorldObjectCollision>& worldObjectCollisions);

    std::list<Impact>& worldObjectImpacts();


protected:
    std::list<Impact> m_worldObjectImpacts;
};

