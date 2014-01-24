#include "hud.h"

#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "etc/windowmanager.h"

#include "utils/tostring.h"
#include "utils/math.h"

#include "player.h"


HUD::HUD(Player* player):
    m_player(player),
    m_crossHair(this),
    m_sphere(glm::vec3(0, 0, 0), 5.0f)
{

}

void HUD::setCrossHairOffset(const glm::vec2& mousePosition) {
    CameraHead& cameraHead = m_player->cameraDolly().cameraHead();

    float fovy = 60.0f;
    float nearZ = 1.0f;
    float d = glm::length(glm::vec2(1.0f, nearZ));

    float nearPlaneHeight = 2 * std::tan(glm::radians(fovy) / 2.0f);
    float nearPlaneWidth = nearPlaneHeight * WindowManager::instance()->aspectRatio();

    glm::vec3 nearPlaneTarget = glm::vec3(mousePosition.x * nearPlaneWidth / 2.0f, mousePosition.y * nearPlaneHeight / 2.0f, -nearZ);

    glm::quat offset = Math::differenceFromViewDirection(nearPlaneTarget);

    m_crossHair.setOrientationOffset(offset);
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
    return m_player->cameraDolly().cameraHead().position() + m_player->cameraDolly().cameraHead().orientation() * m_sphere.position();
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



