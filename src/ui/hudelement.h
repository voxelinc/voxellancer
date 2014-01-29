#pragma once

#include <glm/glm.hpp>

#include "voxel/voxelcluster.h"
#include "geometry/transform.h"

enum HUDOffsetOrigin {
    Center,
    TopLeft,
    Top,
    TopRight,
    Right,
    BottomRight,
    Bottom,
    BottomLeft,
    Left
};

class HUDElement : public VoxelCluster {
public:
    HUDElement();

    glm::vec3 m_offset;
    HUDOffsetOrigin m_origin;
};
