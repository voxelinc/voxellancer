#pragma once
#include <memory>
#include <list>

class Camera;
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
	Camera *m_camera;
	std::unique_ptr<VoxelRenderer> m_voxelRenderer;
	std::list<VoxelCluster> m_elements;
};