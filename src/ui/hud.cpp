#include "hud.h"
#include "camera.h"
#include "voxel\voxelrenderer.h"

HUD::HUD() :
m_camera(0){
	m_voxelRenderer = std::unique_ptr<VoxelRenderer>(new VoxelRenderer());
}

HUD::~HUD(){
}

void HUD::setCamera(Camera *camera){
	m_camera = camera;
}

Camera *HUD::camera(){
	return m_camera;
}

void HUD::update(float delta_sec){

}

void HUD::draw(){
	assert(m_camera != nullptr);

	m_voxelRenderer->prepareDraw(m_camera);

	for (VoxelCluster& element : m_elements)
	{
		m_voxelRenderer->draw(&element);
	}

	m_voxelRenderer->afterDraw();
}