#include "hud.h"
#include "camera.h"
#include "voxel/voxelrenderer.h"
#include "resource/clusterstore.h"
#include "ui/hudelement.h"

HUD::HUD(std::list<VoxelCluster*> ships) :
    m_gameCamera(0),
    m_renderCamera(),
    m_lastGameCamera(),
    m_ships(ships),
    m_shipArrow(),
    m_delta_sec_remain(0),
    m_frameRate(0),
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

    m_renderCamera.setPosition(glm::vec3(0, 0, 0));
    m_renderCamera.setZNear(1.0f);
    m_renderCamera.setZFar(500.0f);
    
    addElement("data/hud/crosshair.csv", HUDOffsetOrigin::Center, glm::vec3(-4, -4, 0), &m_elements);
    addElement("data/hud/topleft.csv", HUDOffsetOrigin::TopLeft, glm::vec3(1, -2, 0), &m_elements);
    addElement("data/hud/topright.csv", HUDOffsetOrigin::TopRight, glm::vec3(-4, -2, 0), &m_elements);
    addElement("data/hud/bottomleft.csv", HUDOffsetOrigin::BottomLeft, glm::vec3(1, 1, 0), &m_elements);
    addElement("data/hud/bottomright.csv", HUDOffsetOrigin::BottomRight, glm::vec3(-4, 1, 0), &m_elements);
    addElement("data/hud/bottom.csv", HUDOffsetOrigin::Bottom, glm::vec3(-27, 1, 0), &m_elements);

    m_shipArrow.reset(ClusterStore::instance()->create<HUDElement>("data/hud/arrow.csv"));
    m_shipArrow->m_origin = HUDOffsetOrigin::Center;
    m_shipArrow->m_offset = glm::vec3(-2, -2, 0);

    loadFonts();

}


void HUD::addElement(const std::string& filename, HUDOffsetOrigin origin, glm::vec3 offset, std::vector<std::unique_ptr<HUDElement>> *list){
    std::unique_ptr<HUDElement> element(ClusterStore::instance()->create<HUDElement>(filename));
    element->m_origin = origin;
    element->m_offset = offset;
    list->push_back(move(element));
}

void HUD::addChar(const std::string& filename, glm::vec3 offset, const char index, std::map<char, std::unique_ptr<VoxelCluster>> *map){
    std::unique_ptr<VoxelCluster> element(ClusterStore::instance()->create<VoxelCluster>(filename));
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
    m_gameCamera = camera;
    m_hudCamera.setOrientation(camera->orientation());
    m_hudCamera.setPosition(camera->position());
}

Camera *HUD::camera(){
    return m_gameCamera;
}

void HUD::stepAnim(glm::vec3 targetPosition, glm::quat targetOrientation){
    // Interpolate between current and target orientation in steps of inertia_rate with inertia multiplier
    m_hudCamera.setOrientation(glm::mix(m_hudCamera.orientation(), targetOrientation, glm::min((1.0f / m_inertia_rate) * m_inertia_rotate, 1.0f)));
    m_hudCamera.setPosition(glm::mix(m_hudCamera.position(), targetPosition, glm::min((1.0f / m_inertia_rate) * m_inertia_move, 1.0f)));
}

void HUD::update(float delta_sec){
    // For a smooth movement we need to simulate 1/inertia_rate "hud steps" per second
    double total = delta_sec + m_delta_sec_remain;
    double progress = 0.0;
	double steptime = 1.0 / m_inertia_rate;
    // progress steps in steptime from 0 to total, rate is the percentage
    while (total - progress > steptime){
        float rate = (float)(progress / total);
        // interpolate algorithm inputs to simluate "missed frames" or hud steps
        // to be as independent of framerate and especially regularity of frame times
        // this assumes the input was constant contious within time from the last frame to now
        stepAnim(glm::mix(m_lastGameCamera.position(), m_gameCamera->position(), rate),
            glm::mix(m_lastGameCamera.orientation(), m_gameCamera->orientation(), rate));
		progress += steptime;
    }
    m_delta_sec_remain = total - progress;

    // Set the lastCamera from which interpolation starts next frame to where we interpolated this time
    m_lastGameCamera.setOrientation(glm::mix(m_lastGameCamera.orientation(), m_gameCamera->orientation(), (float)(progress / total)));
    m_lastGameCamera.setPosition(glm::mix(m_lastGameCamera.position(), m_gameCamera->position(), (float)(progress / total)));

    // framerate measurement (not the best algorithm but the most compact)
    float thisFrame = 1.0f / delta_sec;
    if (thisFrame < 1.0f || thisFrame > 9999.0f) m_frameRate = 0.0f;
    else m_frameRate = m_frameRate * 0.8f + thisFrame * 0.2f;
}

void HUD::draw(){
    assert(m_gameCamera != nullptr);
    glClear(GL_DEPTH_BUFFER_BIT);

    // adjust positions of static hud elements if necessary
    if (m_renderCamera.aspectRatio() != m_gameCamera->aspectRatio() || m_renderCamera.fovy() != m_gameCamera->fovy()){
        adjustPositions();
    }

    // the renderCamera reflects the difference between the virtual hudCamera and the real gameCamera in the HUD coordinate system
    m_renderCamera.setOrientation((glm::inverse(m_hudCamera.orientation()) * m_gameCamera->orientation()));
    m_renderCamera.setPosition(((m_gameCamera->position() - m_hudCamera.position()) * m_move_multiplier.get()) * m_hudCamera.orientation());

    // the virtual voxel display resolution
    float dy = floor(glm::tan(glm::radians(m_renderCamera.fovy() / 2.0f)) * m_distance);
    float dx = m_renderCamera.aspectRatio()*dy;

    m_voxelRenderer->prepareDraw(&m_renderCamera, false);

    // draw statics
    for (std::unique_ptr<HUDElement>& element : m_elements)    {
        m_voxelRenderer->draw(element.get());
    }

    // draw ship arrows
    int i = 0;
    for (VoxelCluster *ship : m_ships){
        if (glm::length(ship->transform().position() - m_hudCamera.position()) < m_arrow_maxdistance){
            // delta is the vector from virtual HUD camera to the ship
            glm::vec3 delta = glm::inverse(m_hudCamera.orientation()) * (ship->transform().position() - m_hudCamera.position());

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
            float degfov = m_renderCamera.fovy() / 2;
            // draw arrow if behind of us or out of "scope"
            if (glm::length(delta) != 0 && (deltaz > 0 || degship / degfov > m_arrow_radius * 1.15f)){
                delta = glm::normalize(delta);
                //rotate arrow towards ship (arrow model points upwards)
                glm::quat absOrientation = glm::angleAxis(glm::degrees(glm::atan(delta.x, delta.y)), glm::vec3(0, 0, -1));
                m_shipArrow->transform().setOrientation(absOrientation);
                // move arrow out of HUD center
                glm::vec3 absPosition = glm::vec3(0, 0, -m_distance) /* move back to HUD pane */
                    /* move m_arrow_radius in direction of heading, where 0 is center 1 is full FOV
                    * because orientation is applied before position, add model-internal offset here */
                    + m_shipArrow->transform().orientation() * (m_shipArrow->m_offset + glm::vec3(0, dy*m_arrow_radius, 0));
                m_shipArrow->transform().setPosition(absPosition);

                m_voxelRenderer->draw(m_shipArrow.get());
            }
        }
    }
    
    // draw frame rate
    if (m_show_framerate){
        drawString(std::to_string((int)glm::round(m_frameRate)), TopLeft, glm::vec3(4, -5, 0), s3x5, 0.8f);
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
    m_renderCamera.setFovy(m_gameCamera->fovy());
    m_renderCamera.setViewport(m_gameCamera->viewport());

    m_dy = floor(glm::tan(glm::radians(m_renderCamera.fovy() / 2.0f)) * m_distance);
    m_dx = m_renderCamera.aspectRatio()*m_dy;

    for (std::unique_ptr<HUDElement>& element : m_elements)    {
        adjustPosition(element.get(), element->m_origin, element->m_offset);
    }
}