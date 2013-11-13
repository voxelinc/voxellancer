#pragma once
#include <memory>
#include <list>

#include <glm/gtx/quaternion.hpp>

#include "camera.h"

class HUDElement;
class VoxelCluster;
class VoxelRenderer;

class HUD {
public:
	HUD();
	virtual ~HUD();

	void setCamera(Camera *camera);
	Camera *camera();

	void update(float delta_sec);
	void draw();

protected:
	void adjustPositions();

	Camera *m_gamecamera;
	Camera m_mycamera;
	glm::quat m_hudorientation;
	std::unique_ptr<VoxelRenderer> m_voxelRenderer;
	std::list<std::unique_ptr<HUDElement>> m_elements;
};