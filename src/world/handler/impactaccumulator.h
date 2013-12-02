#pragma once

#include <list>
#include <map>

#include "collision/collision.h"

#include "world/helper/impact.h"

class Voxel;

class ImpactAccumulator
{
public:
    void clear();

    void parse(const std::list<Impact> &impacts);
//    void parse(const std::list<Impact> &impacts);

    void dontImpact(const std::list<Voxel*> voxels);

//    std::list<Impact> &clusterImpacts();
    std::list<Impact> impacts();


protected:
 //   std::list<Impact> m_clusterImpacts;
    std::map<const Voxel*, Impact> m_voxelImpactMap;
};

