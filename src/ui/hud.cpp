#include "hud.h"

#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "etc/windowmanager.h"

#include "utils/math.h"

#include "player.h"


HUD::HUD(Player* player):
    m_player(player),
    m_crossHair(this),
    m_sphere(glm::vec3(0, 0, 0), 5.0f)
{

}

void HUD::setCrossHairOffset(const glm::vec2& mousePosition) {
    float fovy = 120.0f;
    float nearZ = 1.0f;

    float nearPlaneHeight = 2 * std::sin(glm::radians(fovy) / 2.0f) * nearZ;
    float nearPlaneWidth = nearPlaneHeight * WindowManager::instance()->aspectRatio();

    glm::vec3 target = glm::vec3(mousePosition.x * nearPlaneWidth / 2.0f, mousePosition.y * nearPlaneHeight / 2.0f, -nearZ);

    glm::quat offset = Math::quatFromViewDirection(target);

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
    return m_player->cameraPosition() + m_player->cameraOrientation() * m_sphere.position();
}

glm::quat HUD::orientation() const {
    return m_player->cameraOrientation();
}

void HUD::update(float deltaSec) {
    m_crossHair.update(deltaSec);
}

void HUD::draw() {
    m_crossHair.draw();
}



