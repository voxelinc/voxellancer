#include "hud.h"
#include "camera.h"
#include "voxel/voxelrenderer.h"
#include "clusterloader.h"
#include "ui/hudelement.h"

HUD::HUD(std::list<VoxelCluster*> ships) :
m_gamecamera(0),
m_rendercamera(),
m_lastgamecamera(),
m_ships(ships),
m_shiparrow(),
m_delta_sec_remain(0),
m_framerate(0),
m_distance("hud.distance", 100.f),
m_move_multiplier("hud.move_multiplier", 5.f),
m_inertia_rotate("hud.inertia_rotate", 30.f),
m_inertia_move("hud.inertia_move", 25.f),
m_inertia_rate("hud.inertia_rate", .0005f),
m_arrow_maxdistance("hud.arrow_maxdistance", 1000.f),
m_arrow_radius("hud.arrow_radius", .7f),
m_show_framerate("hud.show_framerate", true)
{
	m_voxelRenderer = std::unique_ptr<VoxelRenderer>(new VoxelRenderer());

	m_rendercamera.setPosition(glm::vec3(0, 0, 0));
	m_rendercamera.setZNear(1.f);
	m_rendercamera.setZFar(500.0f);
	
	ClusterLoader loader;
	addElement(&loader, "data/hud/crosshair.csv", HUDOffsetOrigin::Center, glm::vec3(-4, -4, 0), &m_elements);
	addElement(&loader, "data/hud/topleft.csv", HUDOffsetOrigin::TopLeft, glm::vec3(1, -2, 0), &m_elements);
	addElement(&loader, "data/hud/topright.csv", HUDOffsetOrigin::TopRight, glm::vec3(-4, -2, 0), &m_elements);
	addElement(&loader, "data/hud/bottomleft.csv", HUDOffsetOrigin::BottomLeft, glm::vec3(1, 1, 0), &m_elements);
	addElement(&loader, "data/hud/bottomright.csv", HUDOffsetOrigin::BottomRight, glm::vec3(-4, 1, 0), &m_elements);
	addElement(&loader, "data/hud/bottom.csv", HUDOffsetOrigin::Bottom, glm::vec3(-27, 1, 0), &m_elements);

	addElement(&loader, "data/hud/font/0.csv", HUDOffsetOrigin::TopLeft, glm::vec3(0, -4, 0), &m_numbers);
	addElement(&loader, "data/hud/font/1.csv", HUDOffsetOrigin::TopLeft, glm::vec3(0, -4, 0), &m_numbers);
	addElement(&loader, "data/hud/font/2.csv", HUDOffsetOrigin::TopLeft, glm::vec3(0, -4, 0), &m_numbers);
	addElement(&loader, "data/hud/font/3.csv", HUDOffsetOrigin::TopLeft, glm::vec3(0, -4, 0), &m_numbers);
	addElement(&loader, "data/hud/font/4.csv", HUDOffsetOrigin::TopLeft, glm::vec3(0, -4, 0), &m_numbers);
	addElement(&loader, "data/hud/font/5.csv", HUDOffsetOrigin::TopLeft, glm::vec3(0, -4, 0), &m_numbers);
	addElement(&loader, "data/hud/font/6.csv", HUDOffsetOrigin::TopLeft, glm::vec3(0, -4, 0), &m_numbers);
	addElement(&loader, "data/hud/font/7.csv", HUDOffsetOrigin::TopLeft, glm::vec3(0, -4, 0), &m_numbers);
	addElement(&loader, "data/hud/font/8.csv", HUDOffsetOrigin::TopLeft, glm::vec3(0, -4, 0), &m_numbers);
	addElement(&loader, "data/hud/font/9.csv", HUDOffsetOrigin::TopLeft, glm::vec3(0, -4, 0), &m_numbers);

	m_shiparrow.reset(new HUDElement);
	loader.loadClusterFromFile("data/hud/arrow.csv", m_shiparrow.get());
	m_shiparrow->m_origin = HUDOffsetOrigin::Center;
	m_shiparrow->m_offset = glm::vec3(-2, -2, 0);

}


void HUD::addElement(ClusterLoader *loader, char* filename, HUDOffsetOrigin origin, glm::vec3 offset, std::vector<std::unique_ptr<HUDElement>> *list){
	std::unique_ptr<HUDElement> element(new HUDElement);
	loader->loadClusterFromFile(filename, element.get());
	element->m_origin = origin;
	element->m_offset = offset;
	list->push_back(move(element));
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

void HUD::stepAnim(glm::vec3 targetpos, glm::quat targetor){
	m_hudcamera.setOrientation(glm::mix(m_hudcamera.orientation(), targetor, glm::min(m_inertia_rate * m_inertia_rotate, 1.0f)));
	m_hudcamera.setPosition(glm::mix(m_hudcamera.position(), targetpos, glm::min(m_inertia_rate * m_inertia_move, 1.0f)));
}

void HUD::update(float delta_sec){
	float total = delta_sec + m_delta_sec_remain;
	float progress = 0;
	while (total - progress > m_inertia_rate){
		stepAnim(glm::mix(m_lastgamecamera.position(), m_gamecamera->position(), progress / total),
			glm::mix(m_lastgamecamera.orientation(), m_gamecamera->orientation(), progress / total));
		progress += m_inertia_rate; 
	}
	m_delta_sec_remain = total - progress;
	m_lastgamecamera.setOrientation(m_gamecamera->orientation());
	m_lastgamecamera.setPosition(m_gamecamera->position());

	float thisframe = 1.f / delta_sec;
	if (thisframe < 1 || thisframe > 9999) m_framerate = 0;
	else m_framerate = m_framerate * .8f + thisframe * .2f;
}

void HUD::draw(){
	assert(m_gamecamera != nullptr);
	glClear(GL_DEPTH_BUFFER_BIT);

	if (m_rendercamera.aspectRatio() != m_gamecamera->aspectRatio() || m_rendercamera.fovy() != m_gamecamera->fovy()){
		adjustPositions();
	}

	m_rendercamera.setOrientation((m_gamecamera->orientation()*glm::inverse(m_hudcamera.orientation())));
	m_rendercamera.setPosition(m_hudcamera.orientation() * ((m_gamecamera->position() - m_hudcamera.position()) * m_move_multiplier.get()));

	float dy = floor(glm::tan(glm::radians(m_rendercamera.fovy() / 2)) * m_distance);
	float dx = m_rendercamera.aspectRatio()*dy;

	m_voxelRenderer->prepareDraw(&m_rendercamera, false);

	// draw statics
	for (std::unique_ptr<HUDElement>& element : m_elements)	{
		m_voxelRenderer->draw(element.get());
	}

	// draw ship arrows
	for (VoxelCluster *ship : m_ships){
		if (glm::length(ship->transform().position() - m_hudcamera.position()) < m_arrow_maxdistance){
			// delta is the vector from virtual HUD camera to the ship
			glm::vec3 delta = glm::inverse(m_hudcamera.orientation()) * (ship->transform().position() - m_hudcamera.position());
			// strip z = depth value so glm::length will return x/y-length
			float deltaz = delta.z;
			delta.z = 0;
			// calculate angle of ship and fov
			float len = glm::length(delta);
			float degship = glm::degrees(glm::atan(len, glm::abs(deltaz)));
			float degfov = m_rendercamera.fovy() / 2;
			// draw arrow if behind of us or out of "scope"
			if (glm::length(delta) != 0 && (deltaz > 0 || degship / degfov > m_arrow_radius * 1.15f)){
				delta = glm::normalize(delta);
				//rotate arrow towards ship (arrow model points upwards)
				glm::quat absOrientation = glm::angleAxis(glm::degrees(glm::atan(delta.x, delta.y)), glm::vec3(0, 0, -1));
				m_shiparrow->transform().setOrientation(absOrientation);
				// move arrow out of HUD center
				glm::vec3 absPosition = glm::vec3(0, 0, -m_distance) /* move back to HUD pane */
					/* move m_arrow_radius in direction of heading, where 0 is center 1 is full FOV
					* because orientation is applied before position, add model-internal offset here */
					+ m_shiparrow->transform().orientation() * (m_shiparrow->m_offset + glm::vec3(0, dy*m_arrow_radius, 0));
                m_shiparrow->transform().setPosition(absPosition);

				m_voxelRenderer->draw(m_shiparrow.get());
			}
		}
	}

	// draw frame rate
	if (m_show_framerate){
		int i1, i2;
		if (m_framerate > 99.f){ i1 = 9; i2 = 9; }
		else {
			i1 = (int) glm::floor(m_framerate / 10.f);
			i2 = (int) m_framerate % 10;
		}
		HUDElement *num = m_numbers[i1].get();
		num->transform().setPosition(glm::vec3(-dx + 3, dy - 3, -m_distance) + num->m_offset);
		m_voxelRenderer->draw(num);
		num = m_numbers[i2].get();
        num->transform().setPosition(glm::vec3(-dx + 8, dy - 3, -m_distance) + num->m_offset);
		m_voxelRenderer->draw(num);
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
			element->transform().setPosition(glm::vec3(-dx, dy, -m_distance) + element->m_offset);
			break;
		case Top:
            element->transform().setPosition(glm::vec3(0, dy, -m_distance) + element->m_offset);
			break;
		case TopRight:
            element->transform().setPosition(glm::vec3(dx, dy, -m_distance) + element->m_offset);
			break;
		case Right:
            element->transform().setPosition(glm::vec3(dx, 0, -m_distance) + element->m_offset);
			break;
		case BottomRight:
            element->transform().setPosition(glm::vec3(dx, -dy, -m_distance) + element->m_offset);
			break;
		case Bottom:
            element->transform().setPosition(glm::vec3(0, -dy, -m_distance) + element->m_offset);
			break;
		case BottomLeft:
            element->transform().setPosition(glm::vec3(-dx, -dy, -m_distance) + element->m_offset);
			break;
		case Left:
            element->transform().setPosition(glm::vec3(-dx, 0, -m_distance) + element->m_offset);
			break;
		case Center:
		default:
            element->transform().setPosition(glm::vec3(0, 0, -m_distance) + element->m_offset);
			break;
		}
	}
}