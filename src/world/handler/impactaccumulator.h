#pragma once

#include <list>

#include "collision/collision.h"

#include "impact.h"


class ImpactAccumulator
{
public:
    void clear();

    void parse(const std::list<Impact> &collisions);
//    void parse(const std::list<Impact> &impacts);

//    std::list<Impact> &clusterImpacts();
    std::list<Impact> &impacts();


protected:
 //   std::list<Impact> m_clusterImpacts;
    std::list<Impact> m_impacts;
};

