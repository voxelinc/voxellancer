#pragma once

#include <list>


class CollisionDetector
{
public:
    CollisionDetector(Worldtree &worldtree);
    virtual ~CollisionDetector();

    std::list<Collision> checkCollisions(Voxelcluster *voxelcluster);


protected:
    Worldtree &m_worldtree
};

