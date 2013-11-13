#include "hud.h"
#include "camera.h"
#include "voxel/voxelrenderer.h"
#include "clusterloader.h"
#include "ui/hudelement.h"

static const float hud_depth = -100;

HUD::HUD() :
m_gamecamera(0),
m_mycamera(){
	m_voxelRenderer = std::unique_ptr<VoxelRenderer>(new VoxelRenderer());

	m_mycamera.moveTo(glm::vec3(0, 0, 0));
	m_mycamera.setZNear(0.1f);
	m_mycamera.setZFar(1000.0f);
	
	std::unique_ptr<HUDElement> element;
	element.reset(new HUDElement);
	ClusterLoader loader;
	loader.loadClusterFromFile("data/hud/crosshair.csv", element.get());
	element->m_origin = HUDOffsetOrigin::Center;
	element->m_offset = glm::vec3(-2, -2, 0);
	m_elements.push_back(move(element));

	element.reset(new HUDElement);
	loader.loadClusterFromFile("data/hud/topleft.csv", element.get());
	element->m_origin = HUDOffsetOrigin::TopLeft;
	element->m_offset = glm::vec3(1, -2, 0);
	m_elements.push_back(move(element));

	element.reset(new HUDElement);
	loader.loadClusterFromFile("data/hud/topright.csv", element.get());
	element->m_origin = HUDOffsetOrigin::TopRight;
	element->m_offset = glm::vec3(-4, -2, 0);
	m_elements.push_back(move(element));

	element.reset(new HUDElement);
	loader.loadClusterFromFile("data/hud/bottomleft.csv", element.get());
	element->m_origin = HUDOffsetOrigin::BottomLeft;
	element->m_offset = glm::vec3(1, 1, 0);
	m_elements.push_back(move(element));
	element.reset(new HUDElement);

	loader.loadClusterFromFile("data/hud/bottomright.csv", element.get());
	element->m_origin = HUDOffsetOrigin::BottomRight;
	element->m_offset = glm::vec3(-4, 1, 0);
	m_elements.push_back(move(element));
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

	float dy = floor(glm::tan(glm::radians(m_mycamera.fovy() / 2)) * 100);
	float dx = m_mycamera.aspectRatio()*dy;

	for (std::unique_ptr<HUDElement>& element : m_elements)
	{
		//TODO: we don't need to recalculate every frame, find some way to subscribe to resize event
		switch (element->m_origin){
		case Center:
			element->moveTo(glm::vec3(0, 0, hud_depth) + element->m_offset);
			break;
		case TopLeft:
			element->moveTo(glm::vec3(-dx, dy, hud_depth) + element->m_offset);
			break;
		case TopRight:
			element->moveTo(glm::vec3(dx, dy, hud_depth) + element->m_offset);
			break;
		case BottomLeft:
			element->moveTo(glm::vec3(-dx, -dy, hud_depth) + element->m_offset);
			break;
		case BottomRight:
			element->moveTo(glm::vec3(dx, -dy, hud_depth) + element->m_offset);
			break;
		}

		m_voxelRenderer->draw(element.get());
	}

	m_voxelRenderer->afterDraw();
}