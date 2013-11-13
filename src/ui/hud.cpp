#include "hud.h"
#include "camera.h"
#include "voxel\voxelrenderer.h"
#include "clusterloader.h"

HUD::HUD() :
m_gamecamera(0),
m_mycamera(){
	m_voxelRenderer = std::unique_ptr<VoxelRenderer>(new VoxelRenderer());

	m_mycamera.moveTo(glm::vec3(0, 0, 0));
	m_mycamera.setZNear(0.1f);
	m_mycamera.setZFar(1000.0f);
	
	VoxelCluster element;
	ClusterLoader loader;
	loader.loadClusterFromFile("data/hud/crosshair.zox", &element);
	element.moveTo(glm::vec3(-2, -2, -100));
	m_elements.push_back(element);

}

HUD::~HUD(){
}

void HUD::setCamera(Camera *camera){
	m_gamecamera = camera;
}

Camera *HUD::camera(){
	return m_gamecamera;
}

void HUD::update(float delta_sec){

}

void HUD::draw(){
	assert(m_gamecamera != nullptr);
	glClear(GL_DEPTH_BUFFER_BIT);
	m_mycamera.setFovy(m_gamecamera->fovy());
	m_mycamera.setViewport(m_gamecamera->viewport());


	m_voxelRenderer->prepareDraw(&m_mycamera);

	for (VoxelCluster& element : m_elements)
	{
		m_voxelRenderer->draw(&element);
	}

	m_voxelRenderer->afterDraw();
}