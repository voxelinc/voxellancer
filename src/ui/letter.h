#pragma once

#include <glm/glm.hpp>

#include "voxel/voxelcluster.h"
#include "worldtransform.h"

class Letter : public VoxelCluster {
public:
	Letter(float scale=1.0);
    void setCenter(glm::vec3 center);
    void setScale(float scale);
};
