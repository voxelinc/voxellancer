#include "hud.h"
#include "camera.h"
#include "voxel/voxelrenderer.h"
#include "resource/clustercache.h"
#include "ui/voxelfont.h"
#include "ui/hudelement.h"
#include "world/world.h"
#include "world/god.h"

#include "worldobject/worldobject.h"


HUD::HUD() :
    m_voxelRenderer(new VoxelRenderer()),
    m_font(new VoxelFont()),
    m_gameCamera(0),
    m_renderCamera(),
    m_lastGameCamera(),
    m_shipArrow(),
    m_delta_sec_remain(0),
    m_frameRate(0),
    m_dx(1),
    m_dy(1),
    prop_distance("hud.distance"),
    prop_moveMultiplier("hud.moveMultiplier"),
    prop_inertiaRotate("hud.inertiaRotate"),
    prop_inertiaMove("hud.inertiaMove"),
    prop_inertiaRate("hud.inertiaRate"),
    prop_arrowMaxdistance("hud.arrowMaxdistance"),
    prop_arrowRadius("hud.arrowRadius"),
    prop_showFramerate("hud.showFramerate")
{
    m_font->setRenderer(m_voxelRenderer.get());

    m_renderCamera.setPosition(glm::vec3(0, 0, 0));
    m_renderCamera.setZNear(1.0f);
    m_renderCamera.setZFar(500.0f);


    addElement("data/hud/crosshair.csv", HUDOffsetOrigin::Center, glm::vec3(-4, -4, 0), &m_elements);
    addElement("data/hud/topleft.csv", HUDOffsetOrigin::TopLeft, glm::vec3(1, -2, 0), &m_elements);
    addElement("data/hud/topright.csv", HUDOffsetOrigin::TopRight, glm::vec3(-4, -2, 0), &m_elements);
    addElement("data/hud/bottomleft.csv", HUDOffsetOrigin::BottomLeft, glm::vec3(1, 1, 0), &m_elements);
    addElement("data/hud/bottomright.csv", HUDOffsetOrigin::BottomRight, glm::vec3(-4, 1, 0), &m_elements);
    addElement("data/hud/bottom.csv", HUDOffsetOrigin::Bottom, glm::vec3(-27, 1, 0), &m_elements);

    m_shipArrow.reset(new HUDElement());
    ClusterCache::instance()->fill(m_shipArrow.get(), "data/hud/arrow.csv");
    m_shipArrow->m_origin = HUDOffsetOrigin::Center;
    m_shipArrow->m_offset = glm::vec3(-2, -2, 0);
}

void HUD::addElement(const std::string& filename, HUDOffsetOrigin origin, glm::vec3 offset, std::vector<std::unique_ptr<HUDElement>> *list){
    std::unique_ptr<HUDElement> element(new HUDElement());
    ClusterCache::instance()->fill(element.get(), filename);
    element->m_origin = origin;
    element->m_offset = offset;
    list->push_back(move(element));
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
    m_hudCamera.setOrientation(glm::slerp(m_hudCamera.orientation(), targetOrientation, glm::min((1.0f / prop_inertiaRate) * prop_inertiaRotate, 1.0f)));
    m_hudCamera.setPosition(glm::mix(m_hudCamera.position(), targetPosition, glm::min((1.0f / prop_inertiaRate) * prop_inertiaMove, 1.0f)));
}

void HUD::update(float delta_sec){
    // For a smooth movement we need to simulate 1/inertia_rate "hud steps" per second
    double total = delta_sec + m_delta_sec_remain;
    double progress = 0.0;
	double steptime = 1.0 / prop_inertiaRate;
    // progress steps in steptime from 0 to total, rate is the percentage
    while (total - progress > steptime){
        float rate = (float)(progress / total);
        // interpolate algorithm inputs to simluate "missed frames" or hud steps
        // to be as independent of framerate and especially regularity of frame times
        // this assumes the input was constant contious within time from the last frame to now
        stepAnim(glm::mix(m_lastGameCamera.position(), m_gameCamera->position(), rate),
            glm::slerp(m_lastGameCamera.orientation(), m_gameCamera->orientation(), rate));
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
    m_renderCamera.setPosition(((m_gameCamera->position() - m_hudCamera.position()) * prop_moveMultiplier.get()) * m_hudCamera.orientation());

    m_voxelRenderer->prepareDraw(&m_renderCamera, false);

    // draw statics
    for (std::unique_ptr<HUDElement>& element : m_elements){
        m_voxelRenderer->draw(element.get());
    }

    // draw ship arrows
    int i = 0;
    for (WorldObject *ship : World::instance()->worldObjects()) {
        // TODO something like "if (ship->hudData->shouldShowOnHud())"
        if (glm::length(ship->transform().position() - m_hudCamera.position()) < prop_arrowMaxdistance){
            // delta is the vector from virtual HUD camera to the ship
            glm::vec3 delta = glm::inverse(m_hudCamera.orientation()) * (ship->transform().position() - m_hudCamera.position());

            if (i < 11){
                std::stringstream s; s.setf(std::ios::fixed, std::ios::floatfield); s.precision(2);
                s << ship->hudInfo().name() << ": " << ship->voxelMap().size() << "/" << (float)glm::length(delta);
                m_font->drawString(s.str(), calculatePosition(BottomLeft, glm::vec3(4, 5 + 4 * i, 0)), s5x7, 0.4f);
                i++;
            } else if (i == 11){
                m_font->drawString("-more-", calculatePosition(BottomLeft, glm::vec3(4, 5 + 4 * i, 0)), s5x7, 0.4f);
            }

            if (ship->hudInfo().showOnHud()){
                // strip z = depth value so glm::length will return x/y-length
                float deltaz = delta.z;
                delta.z = 0;
                // calculate angle of ship and fov
                float len = glm::length(delta);
                float degship = glm::degrees(glm::atan(len, glm::abs(deltaz)));
                float degfov = m_renderCamera.fovy() / 2;
                // draw arrow if behind of us or out of "scope"
                if (glm::length(delta) != 0 && (deltaz > 0 || degship / degfov > prop_arrowRadius * 1.15f)){
                    delta = glm::normalize(delta);
                    //rotate arrow towards ship (arrow model points upwards)
                    glm::quat absOrientation = glm::angleAxis(glm::degrees(glm::atan(delta.x, delta.y)), glm::vec3(0, 0, -1));
                    m_shipArrow->transform().setOrientation(absOrientation);
                    // move arrow out of HUD center
                    glm::vec3 absPosition = glm::vec3(0, 0, -prop_distance) /* move back to HUD pane */
                        /* move m_arrow_radius in direction of heading, where 0 is center 1 is full FOV
                        * because orientation is applied before position, add model-internal offset here */
                        + m_shipArrow->transform().orientation() * (m_shipArrow->m_offset + glm::vec3(0, m_dy * prop_arrowRadius, 0));
                    m_shipArrow->transform().setPosition(absPosition);

                    m_voxelRenderer->draw(m_shipArrow.get());
                }
            }
        }
    }

    // draw frame rate
    if (prop_showFramerate){
        m_font->drawString(std::to_string((int)glm::round(m_frameRate)), calculatePosition(TopLeft, glm::vec3(4, -5, 0)), s3x5, 0.8f);
    }

    m_font->drawString("NO TARGET", calculatePosition(Bottom, glm::vec3(0, 8, 0)), s3x5, 0.5f, aCenter);

    m_voxelRenderer->afterDraw();

}

glm::vec3 HUD::calculatePosition(HUDOffsetOrigin origin, glm::vec3 offset){
    switch (origin){
    case TopLeft:
        return glm::vec3(-m_dx, m_dy, -prop_distance) + offset;
        break;
    case Top:
        return glm::vec3(0, m_dy, -prop_distance) + offset;
        break;
    case TopRight:
        return glm::vec3(m_dx, m_dy, -prop_distance) + offset;
        break;
    case Right:
        return glm::vec3(m_dx, 0, -prop_distance) + offset;
        break;
    case BottomRight:
        return glm::vec3(m_dx, -m_dy, -prop_distance) + offset;
        break;
    case Bottom:
        return glm::vec3(0, -m_dy, -prop_distance) + offset;
        break;
    case BottomLeft:
        return glm::vec3(-m_dx, -m_dy, -prop_distance) + offset;
        break;
    case Left:
        return glm::vec3(-m_dx, 0, -prop_distance) + offset;
        break;
    case Center:
    default:
        return glm::vec3(0, 0, -prop_distance) + offset;
        break;
    }
}



void HUD::adjustPositions(){
    m_renderCamera.setFovy(m_gameCamera->fovy());
    m_renderCamera.setViewport(m_gameCamera->viewport());

    m_dy = floor(glm::tan(glm::radians(m_renderCamera.fovy() / 2.0f)) * prop_distance);
    m_dx = m_renderCamera.aspectRatio()*m_dy;

    for (std::unique_ptr<HUDElement>& element : m_elements)    {
        element->transform().setPosition(calculatePosition(element->m_origin, element->m_offset));
    }
}
