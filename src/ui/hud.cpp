#include "hud.h"
#include "camera.h"
#include "voxel/voxelrenderer.h"
#include "clusterloader.h"
#include "ui/hudelement.h"


HUD::HUD() :
m_gamecamera(0),
m_rendercamera(),
m_distance("hud.distance", 100.f),
m_move_multiplier("hud.move_multiplier", 5.f),
m_inertia_rotate("hud.inertia_rotate", 30.f),
m_inertia_move("hud.inertia_move", 25.f)
{
	m_voxelRenderer = std::unique_ptr<VoxelRenderer>(new VoxelRenderer());

	m_rendercamera.moveTo(glm::vec3(0, 0, 0));
	m_rendercamera.setZNear(0.1f);
	m_rendercamera.setZFar(1000.0f);
	
	std::unique_ptr<HUDElement> element;
	element.reset(new HUDElement);
	ClusterLoader loader;
	loader.loadClusterFromFile("data/hud/crosshair.csv", element.get());
	element->m_origin = HUDOffsetOrigin::Center;
	element->m_offset = glm::vec3(-4, -4, 0);
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
	m_hudcamera.rotateTo(camera->orientation());
	m_hudcamera.moveTo(camera->position());
}

Camera *HUD::camera(){
	return m_gamecamera;
}

void HUD::update(float delta_sec){
	m_hudcamera.rotateTo(glm::mix(m_hudcamera.orientation() , m_gamecamera->orientation(), glm::min(delta_sec * 30.f, 1.0f)));
	m_hudcamera.moveTo(glm::mix(m_hudcamera.position(), m_gamecamera->position(), glm::min(delta_sec * 20.f, 1.0f)));
}

void HUD::draw(){
	assert(m_gamecamera != nullptr);
	glClear(GL_DEPTH_BUFFER_BIT);

	if (m_rendercamera.aspectRatio() != m_gamecamera->aspectRatio() || m_rendercamera.fovy() != m_gamecamera->fovy()){
		adjustPositions();
	}

	m_rendercamera.rotateTo((m_gamecamera->orientation()*glm::inverse(m_hudcamera.orientation())));
	m_rendercamera.moveTo(m_hudcamera.orientation() * ((m_gamecamera->position() - m_hudcamera.position()) * m_move_multiplier.get()));

	m_voxelRenderer->prepareDraw(&m_rendercamera);

	for (std::unique_ptr<HUDElement>& element : m_elements)	{
		m_voxelRenderer->draw(element.get());
	}

	m_voxelRenderer->afterDraw();
}

void HUD::adjustPositions(){
	m_rendercamera.setFovy(m_gamecamera->fovy());
	m_rendercamera.setViewport(m_gamecamera->viewport());

	float dy = floor(glm::tan(glm::radians(m_rendercamera.fovy() / 2)) * 100);
	float dx = m_rendercamera.aspectRatio()*dy;

	for (std::unique_ptr<HUDElement>& element : m_elements)	{
		//TODO: we don't need to recalculate every frame, find some way to subscribe to resize event
		switch (element->m_origin){
		case Center:
			element->moveTo(glm::vec3(0, 0, -m_distance) + element->m_offset);
			break;
		case TopLeft:
			element->moveTo(glm::vec3(-dx, dy, -m_distance) + element->m_offset);
			break;
		case TopRight:
			element->moveTo(glm::vec3(dx, dy, -m_distance) + element->m_offset);
			break;
		case BottomLeft:
			element->moveTo(glm::vec3(-dx, -dy, -m_distance) + element->m_offset);
			break;
		case BottomRight:
			element->moveTo(glm::vec3(dx, -dy, -m_distance) + element->m_offset);
			break;
		}
	}
}