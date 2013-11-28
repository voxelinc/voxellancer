#include "hud.h"
#include "camera.h"
#include "voxel/voxelrenderer.h"
#include "resource/clustercache.h"
#include "ui/hudelement.h"
#include "world/world.h"
#include "world/god.h"
#include "world/worldobject.h"

HUD::HUD() :
m_gamecamera(0),
m_rendercamera(),
m_lastgamecamera(),
m_shiparrow(),
m_delta_sec_remain(0),
m_framerate(0),
m_dx(1),
m_dy(1),
m_distance("hud.distance"),
m_move_multiplier("hud.move_multiplier"),
m_inertia_rotate("hud.inertia_rotate"),
m_inertia_move("hud.inertia_move"),
m_inertia_rate("hud.inertia_rate"),
m_arrow_maxdistance("hud.arrow_maxdistance"),
m_arrow_radius("hud.arrow_radius"),
m_show_framerate("hud.show_framerate")
{
    m_voxelRenderer = std::unique_ptr<VoxelRenderer>(new VoxelRenderer());

    m_rendercamera.setPosition(glm::vec3(0, 0, 0));
    m_rendercamera.setZNear(1.0f);
    m_rendercamera.setZFar(500.0f);
    
    addElement("data/hud/crosshair.csv", HUDOffsetOrigin::Center, glm::vec3(-4, -4, 0), &m_elements);
    addElement("data/hud/topleft.csv", HUDOffsetOrigin::TopLeft, glm::vec3(1, -2, 0), &m_elements);
    addElement("data/hud/topright.csv", HUDOffsetOrigin::TopRight, glm::vec3(-4, -2, 0), &m_elements);
    addElement("data/hud/bottomleft.csv", HUDOffsetOrigin::BottomLeft, glm::vec3(1, 1, 0), &m_elements);
    addElement("data/hud/bottomright.csv", HUDOffsetOrigin::BottomRight, glm::vec3(-4, 1, 0), &m_elements);
    addElement("data/hud/bottom.csv", HUDOffsetOrigin::Bottom, glm::vec3(-27, 1, 0), &m_elements);

    m_shiparrow.reset(new HUDElement());
    ClusterCache::instance()->fillCluster(m_shiparrow.get(), "data/hud/arrow.csv");
    m_shiparrow->m_origin = HUDOffsetOrigin::Center;
    m_shiparrow->m_offset = glm::vec3(-2, -2, 0);

    loadFonts();

}


void HUD::addElement(const std::string& filename, HUDOffsetOrigin origin, glm::vec3 offset, std::vector<std::unique_ptr<HUDElement>> *list){
    std::unique_ptr<HUDElement> element(new HUDElement());
    ClusterCache::instance()->fillCluster(element.get(), filename);
    element->m_origin = origin;
    element->m_offset = offset;
    list->push_back(move(element));
}

void HUD::addChar(const std::string& filename, glm::vec3 offset, const char index, std::map<char, std::unique_ptr<VoxelCluster>> *map){
    std::unique_ptr<VoxelCluster> element(new VoxelCluster());
    ClusterCache::instance()->fillCluster(element.get(), filename);
    element->transform().setCenter(offset);
    (*map)[index] = move(element);
}

void HUD::loadFont(const std::string& identifier, glm::vec3 offset, std::map<char, std::unique_ptr<VoxelCluster>> *map){
    const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < 36; i++){
        std::string path = "data/hud/font/" + identifier + "/";
        path.append(&letters[i], 1);
        path.append(".csv");
        addChar(path, offset, letters[i], map);
    }
    // non-letters the fs might/does not like
    addChar("data/hud/font/" + identifier + "/_dot.csv", offset, '.', map);
    addChar("data/hud/font/" + identifier + "/_comma.csv", offset, ',', map);
    addChar("data/hud/font/" + identifier + "/_colon.csv", offset, ':', map);
    addChar("data/hud/font/" + identifier + "/_semicolon.csv", offset, ';', map);
    addChar("data/hud/font/" + identifier + "/_slash.csv", offset, '/', map);
    addChar("data/hud/font/" + identifier + "/_backslash.csv", offset, '\\', map);
    addChar("data/hud/font/" + identifier + "/_underscore.csv", offset, '_', map);
    addChar("data/hud/font/" + identifier + "/_dash.csv", offset, '-', map);
}

void HUD::loadFonts(){
    loadFont("3x5", glm::vec3(1, 2, 0), &m_font3x5);
    loadFont("5x7", glm::vec3(2, 3, 0), &m_font5x7);
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
    m_hudcamera.setOrientation(glm::mix(m_hudcamera.orientation(), targetor, glm::min((1.0f / m_inertia_rate) * m_inertia_rotate, 1.0f)));
    m_hudcamera.setPosition(glm::mix(m_hudcamera.position(), targetpos, glm::min((1.0f / m_inertia_rate) * m_inertia_move, 1.0f)));
}

void HUD::update(float delta_sec){
    double total = delta_sec + m_delta_sec_remain;
    double progress = 0.0;
	double steptime = 1.0 / m_inertia_rate;
	while (total - progress > steptime){
		float rate = (float) (progress / total);
        stepAnim(glm::mix(m_lastgamecamera.position(), m_gamecamera->position(), rate),
            glm::mix(m_lastgamecamera.orientation(), m_gamecamera->orientation(), rate));
		progress += steptime;
    }
    m_delta_sec_remain = total - progress;
    m_lastgamecamera.setOrientation(m_gamecamera->orientation());
    m_lastgamecamera.setPosition(m_gamecamera->position());

    float thisframe = 1.0f / delta_sec;
    if (thisframe < 1.0f || thisframe > 9999.0f) m_framerate = 0.0f;
    else m_framerate = m_framerate * 0.8f + thisframe * 0.2f;
}

void HUD::draw(){
    assert(m_gamecamera != nullptr);
    glClear(GL_DEPTH_BUFFER_BIT);

    if (m_rendercamera.aspectRatio() != m_gamecamera->aspectRatio() || m_rendercamera.fovy() != m_gamecamera->fovy()){
        adjustPositions();
    }

    m_rendercamera.setOrientation((glm::inverse(m_hudcamera.orientation()) * m_gamecamera->orientation()));
    m_rendercamera.setPosition(((m_gamecamera->position() - m_hudcamera.position()) * m_move_multiplier.get()) * m_hudcamera.orientation());

    float dy = floor(glm::tan(glm::radians(m_rendercamera.fovy() / 2.0f)) * m_distance);
    float dx = m_rendercamera.aspectRatio()*dy;

    m_voxelRenderer->prepareDraw(&m_rendercamera, false);

    // draw statics
    for (std::unique_ptr<HUDElement>& element : m_elements){
        m_voxelRenderer->draw(element.get());
    }

    // draw ship arrows
    int i = 0;
    for (WorldObject *ship : World::instance()->clusters()) {
        // TODO something like "if (ship->hudData->shouldShowOnHud())"
        if (glm::length(ship->transform().position() - m_hudcamera.position()) < m_arrow_maxdistance){
            // delta is the vector from virtual HUD camera to the ship
            glm::vec3 delta = glm::inverse(m_hudcamera.orientation()) * (ship->transform().position() - m_hudcamera.position());

            std::stringstream s; s.setf(std::ios::fixed, std::ios::floatfield); s.precision(2);
            s << "Dist " << i << ": " << (float)glm::length(delta);
            drawString(s.str(), BottomLeft, glm::vec3(4, 5 + 5 * i, 0), s5x7, 0.5f);
            i++;

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
        drawString(std::to_string((int)glm::round(m_framerate)), TopLeft, glm::vec3(4, -5, 0), s3x5, 0.8f);
    }

    drawString("NO TARGET", Bottom, glm::vec3(0, 8, 0), s3x5, 0.5f, aCenter);

    m_voxelRenderer->afterDraw();

}

// m_voxelRenderer must be prepared to draw
void HUD::drawString(std::string text, HUDOffsetOrigin origin, glm::vec3 offset, HUDFontSize size, float scale, HUDFontAlign align){
    std::transform(text.begin(), text.end(), text.begin(), ::toupper);
    std::map<char, std::unique_ptr<VoxelCluster>> *source;
    float width;
    float intoffset;
    switch (size){
    case s5x7:
        source = &m_font5x7;
        width = 7 * scale;
        break;
    case s3x5:
    default:
        source = &m_font3x5;
        width = 5 * scale;
        break;
    }
    switch (align){
    case aRight:
        intoffset = -1.f * (text.length()-1) * width;
        break;
    case aCenter:
        intoffset = -1.f * ((text.length()-1) / 2.0f) * width;
        break;
    case aLeft:
    default:
        intoffset = 0;
        break;
    }

    for (int i = 0; i < text.length(); i++){
        VoxelCluster *cl = (*source)[text[i]].get();
        if (cl != nullptr){
            adjustPosition(cl, origin, offset + glm::vec3(intoffset + width * i, 0, 0));
            cl->transform().setScale(scale);
            m_voxelRenderer->draw(cl);
        }
    }
}

void HUD::adjustPosition(VoxelCluster *cluster, HUDOffsetOrigin origin, glm::vec3 offset){
    assert(cluster != nullptr);
    switch (origin){
    case TopLeft:
        cluster->transform().setPosition(glm::vec3(-m_dx, m_dy, -m_distance) + offset);
        break;
    case Top:
        cluster->transform().setPosition(glm::vec3(0, m_dy, -m_distance) + offset);
        break;
    case TopRight:
        cluster->transform().setPosition(glm::vec3(m_dx, m_dy, -m_distance) + offset);
        break;
    case Right:
        cluster->transform().setPosition(glm::vec3(m_dx, 0, -m_distance) + offset);
        break;
    case BottomRight:
        cluster->transform().setPosition(glm::vec3(m_dx, -m_dy, -m_distance) + offset);
        break;
    case Bottom:
        cluster->transform().setPosition(glm::vec3(0, -m_dy, -m_distance) + offset);
        break;
    case BottomLeft:
        cluster->transform().setPosition(glm::vec3(-m_dx, -m_dy, -m_distance) + offset);
        break;
    case Left:
        cluster->transform().setPosition(glm::vec3(-m_dx, 0, -m_distance) + offset);
        break;
    case Center:
    default:
        cluster->transform().setPosition(glm::vec3(0, 0, -m_distance) + offset);
        break;
    }
}

void HUD::adjustPositions(){
    m_rendercamera.setFovy(m_gamecamera->fovy());
    m_rendercamera.setViewport(m_gamecamera->viewport());

    m_dy = floor(glm::tan(glm::radians(m_rendercamera.fovy() / 2.0f)) * m_distance);
    m_dx = m_rendercamera.aspectRatio()*m_dy;

    for (std::unique_ptr<HUDElement>& element : m_elements)    {
        adjustPosition(element.get(), element->m_origin, element->m_offset);
    }
}