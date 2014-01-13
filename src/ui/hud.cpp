#include "hud.h"

#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "utils/tostring.h"
#include "utils/math.h"

#include "player.h"


HUD::HUD(Player* player):
    m_player(player),
    m_crossHair(this),
    m_sphere(glm::vec3(0, 0, 0), 5.0f)
{

}

void HUD::setCrossHairOffset(const glm::vec2& planeOffset) {
    CameraHead& cameraHead = m_player->cameraDolly().cameraHead();

    float vsh = std::sin(glm::radians(cameraHead.fovy() / 2.0f)) * cameraHead.nearZ();
    float vsw = vsh * cameraHead.aspectRatio();

    glm::vec3 onNP;
    onNP = glm::vec3(planeOffset.x * vsw, planeOffset.y * vsh, 0);
    onNP = cameraHead.orientation() * onNP;
    onNP = onNP + glm::vec3(0, 0, -cameraHead.nearZ());
    onNP = cameraHead.orientation() * onNP + cameraHead.position();
    glm::vec3 dir = onNP - position();

//    glm::vec3 np = cameraHead.position() + cameraHead.orientation() * glm::vec3(0, 0, -cameraHead.nearZ());
//    glm::vec3 ch = onNP + np;
//    glm::vec3 dir = ch - position();

    glm::quat o = Math::quatFromDir(dir) * glm::inverse(cameraHead.orientation());

    m_crossHair.setDirectionOffset(o);
}

Player* HUD::player() {
    return m_player;
}

const Sphere& HUD::sphere() const {
    return m_sphere;
}

CrossHair& HUD::crossHair() {
    return m_crossHair;
}

glm::vec3 HUD::position() const {
    return m_player->cameraDolly().cameraHead().position() + m_sphere.position();
}

glm::quat HUD::orientation() const {
    return m_player->cameraDolly().cameraHead().orientation();
}

void HUD::update(float deltaSec) {
    m_crossHair.update(deltaSec);
}

void HUD::draw() {
    m_crossHair.draw();
}

