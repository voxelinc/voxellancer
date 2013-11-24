#pragma once

#include <glm/glm.hpp>

#include "voxel/voxelcluster.h"

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
	HUDElement(const VoxelCluster& other);

	glm::vec3 m_offset;
	HUDOffsetOrigin m_origin;
};