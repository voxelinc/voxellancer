#pragma once
#include <memory>
#include <list>

#include "camera.h"

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
	Camera *m_gamecamera;
	Camera m_mycamera;
	std::unique_ptr<VoxelRenderer> m_voxelRenderer;
	std::list<VoxelCluster> m_elements;
};