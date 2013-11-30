#pragma once

#include <glm/glm.hpp>

#include "voxel/voxelcluster.h"
#include "world/drawable.h"
#include "worldtransform.h"

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

class HUDElement : public VoxelCluster, public Drawable {
public:
	HUDElement();
    HUDElement(const HUDElement& other);

    virtual VoxelCluster * voxelCluster() override;
    virtual glm::mat4 matrix() override;

    WorldTransform m_transform;
	glm::vec3 m_offset;
	HUDOffsetOrigin m_origin;
};