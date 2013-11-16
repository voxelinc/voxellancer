#include "hud.h"
#include "camera.h"
#include "voxel/voxelrenderer.h"
#include "clusterloader.h"
#include "ui/hudelement.h"


HUD::HUD(std::list<VoxelCluster*> ships) :
m_gamecamera(0),
m_rendercamera(),
m_ships(ships),
m_shiparrow(),
m_distance("hud.distance", 100.f),
m_move_multiplier("hud.move_multiplier", 5.f),
m_inertia_rotate("hud.inertia_rotate", 30.f),
m_inertia_move("hud.inertia_move", 25.f),
m_arrow_maxdistance("hud.arrow_maxdistance", 1000.f),
m_arrow_radius("hud.arrow_radius", .7f)
{
	m_voxelRenderer = std::unique_ptr<VoxelRenderer>(new VoxelRenderer());

	m_rendercamera.setPosition(glm::vec3(0, 0, 0));
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

	element.reset(new HUDElement);
	loader.loadClusterFromFile("data/hud/bottom.csv", element.get());
	element->m_origin = HUDOffsetOrigin::Bottom;
	element->m_offset = glm::vec3(-27, 1, 0);
	m_elements.push_back(move(element));


	m_shiparrow.reset(new HUDElement);
	loader.loadClusterFromFile("data/hud/arrow.csv", m_shiparrow.get());
	m_shiparrow->m_origin = HUDOffsetOrigin::Center;
	m_shiparrow->m_offset = glm::vec3(-2, -2, 0);

}

HUD::~HUD(){
}

void HUD::setCamera(Camera *camera){
	m_gamecamera = camera;
	m_hudcamera.setOrientation(camera->orientation());
	m_hudcamera.setPosition(camera->position());
}

Camera *HUD::camera(){
	return m_gamecamera;
}

void HUD::update(float delta_sec){
	m_hudcamera.setOrientation(glm::mix(m_hudcamera.orientation() , m_gamecamera->orientation(), glm::min(delta_sec * m_inertia_rotate, 1.0f)));
	m_hudcamera.setPosition(glm::mix(m_hudcamera.position(), m_gamecamera->position(), glm::min(delta_sec * m_inertia_move, 1.0f)));
}

void HUD::draw(){
	assert(m_gamecamera != nullptr);
	glClear(GL_DEPTH_BUFFER_BIT);

	if (m_rendercamera.aspectRatio() != m_gamecamera->aspectRatio() || m_rendercamera.fovy() != m_gamecamera->fovy()){
		adjustPositions();
	}

	m_rendercamera.setOrientation((m_gamecamera->orientation()*glm::inverse(m_hudcamera.orientation())));
	m_rendercamera.setPosition(m_hudcamera.orientation() * ((m_gamecamera->position() - m_hudcamera.position()) * m_move_multiplier.get()));

	m_voxelRenderer->prepareDraw(&m_rendercamera);

	// draw statics
	for (std::unique_ptr<HUDElement>& element : m_elements)	{
		m_voxelRenderer->draw(element.get());
	}

	// draw ship arrows
	float dy = floor(glm::tan(glm::radians(m_rendercamera.fovy() / 2)) * m_distance);
	for (VoxelCluster *ship : m_ships){
		if (glm::length(ship->worldTransform().position() - m_hudcamera.position()) < m_arrow_maxdistance){
			glm::vec3 delta = m_hudcamera.orientation() * (ship->worldTransform().position() - m_hudcamera.position());
			float deltaz = delta.z;
			delta.z = 0;
			// if behind of us or out of "scope"
			float degarr = glm::degrees(glm::atan(glm::length(delta), glm::abs(deltaz)));
			float degfov = m_rendercamera.fovy() / 2;
			if (deltaz > 0 || degarr / degfov > m_arrow_radius * 1.15f){
				delta = glm::normalize(delta);
				//m_shiparrow->rotateTo(glm::angleAxis(glm::degrees(glm::atan(delta.x, delta.y)), glm::vec3(0, 0, -1)));
				//m_shiparrow->moveTo(glm::vec3(0, 0, -m_distance)
				//	+ m_shiparrow->transform.orientation() * (m_shiparrow->m_offset + glm::vec3(0, dy*m_arrow_radius, 0)));
				m_shiparrow->transform(WorldTransform(glm::angleAxis(glm::degrees(glm::atan(delta.x, delta.y)), glm::vec3(0, 0, -1)) * glm::inverse(m_shiparrow->worldTransform().orientation())));
				m_shiparrow->transform(-m_shiparrow->worldTransform().position() + glm::vec3(0, 0, -m_distance)
					+ m_shiparrow->worldTransform().orientation() * (m_shiparrow->m_offset + glm::vec3(0, dy*m_arrow_radius, 0)));
				m_voxelRenderer->draw(m_shiparrow.get());
			}
		}
	}

	m_voxelRenderer->afterDraw();
}

void HUD::adjustPositions(){
	m_rendercamera.setFovy(m_gamecamera->fovy());
	m_rendercamera.setViewport(m_gamecamera->viewport());

	float dy = floor(glm::tan(glm::radians(m_rendercamera.fovy() / 2)) * m_distance);
	float dx = m_rendercamera.aspectRatio()*dy;

	for (std::unique_ptr<HUDElement>& element : m_elements)	{
		switch (element->m_origin){
		case TopLeft:
			//element->moveTo(glm::vec3(-dx, dy, -m_distance) + element->m_offset);
			element->transform(-element->worldTransform().position() + glm::vec3(-dx, dy, -m_distance) + element->m_offset);
			break;
		case Top:
			element->transform(-element->worldTransform().position() + glm::vec3(0, dy, -m_distance) + element->m_offset);
			break;
		case TopRight:
			element->transform(-element->worldTransform().position() + glm::vec3(dx, dy, -m_distance) + element->m_offset);
			break;
		case Right:
			element->transform(-element->worldTransform().position() + glm::vec3(dx, 0, -m_distance) + element->m_offset);
			break;
		case BottomRight:
			element->transform(-element->worldTransform().position() + glm::vec3(dx, -dy, -m_distance) + element->m_offset);
			break;
		case Bottom:
			element->transform(-element->worldTransform().position() + glm::vec3(0, -dy, -m_distance) + element->m_offset);
			break;
		case BottomLeft:
			element->transform(-element->worldTransform().position() + glm::vec3(-dx, -dy, -m_distance) + element->m_offset);
			break;
		case Left:
			element->transform(-element->worldTransform().position() + glm::vec3(-dx, 0, -m_distance) + element->m_offset);
			break;
		case Center:
		default:
			element->transform(-element->worldTransform().position() + glm::vec3(0, 0, -m_distance) + element->m_offset);
			break;
		}
	}
}