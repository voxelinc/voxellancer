#pragma once

#include <glm/glm.hpp>

#include "worldtransform.h"
#include "geometry/aabb.h"

class Voxelcluster
{
public:
    Voxelcluster();
    virtual ~Voxelcluster();

    const AABB &aabb();

protected:
    glm::vec3 m_rotationCenter;
    WorldTransform m_worldTransform;
    AABB m_aabb;
};

