#pragma once

#include <glm/glm.hpp>

#include "voxel/voxelcluster.h"
#include "world/drawable.h"
#include "worldtransform.h"


class Letter : public Drawable {
public:
    Letter();
    virtual ~Letter();

    virtual VoxelCluster * voxelCluster();
    virtual WorldTransform& transform();

    WorldTransform m_transform;
    VoxelCluster m_voxelCluster;
};