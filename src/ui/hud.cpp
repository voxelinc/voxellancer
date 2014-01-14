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

    float nearPlaneHeight = 2 * std::sin(glm::radians(cameraHead.fovy()) / 2.0f) * cameraHead.nearZ();
    float nearPlaneWidth = nearPlaneHeight * cameraHead.aspectRatio();

    glm::vec3 target = glm::vec3(planeOffset.x * nearPlaneWidth / 2.0f, planeOffset.y * nearPlaneHeight / 2.0f,-cameraHead.nearZ());

    glm::quat offset = Math::quatFromDir(target);

    m_crossHair.setDirectionOffset(offset);
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

void HUD::printLine(std::string line){

}

