#pragma once

#include <list>
#include "collision/collision.h"
#include "world/helper/impact.h"

class Mover
{
public:
    void moveWorldObjects(float deltaSec);

    const std::list<Impact> &impacts();


protected:
    std::list<Impact> m_impacts;
};

