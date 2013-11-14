#pragma once
#include <memory>
#include <list>

#include <glm/gtx/quaternion.hpp>

#include "property/property.h"
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
	WorldObject m_hudcamera;
	Camera m_rendercamera;
	std::unique_ptr<VoxelRenderer> m_voxelRenderer;
	std::list<std::unique_ptr<HUDElement>> m_elements;

	Property<float> m_inertia_move, m_inertia_rotate, m_move_multiplier, m_distance;
};