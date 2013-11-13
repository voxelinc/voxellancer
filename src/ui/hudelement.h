#pragma once

#include <glm/glm.hpp>

#include "voxel\voxelcluster.h"

enum HUDOffsetOrigin {
	Center,
	TopLeft,
	TopRight,
	BottomLeft,
	BottomRight
};

class HUDElement : public VoxelCluster {
public:
	HUDElement();

	glm::vec3 m_offset;
	HUDOffsetOrigin m_origin;
};