#include "hud.h"

#include "player.h"

HUD::HUD(Player* player):
    m_player(player),
    m_crossHair(this),
    m_sphere(glm::vec3(0, 0, 0), 5.0f)
{

}

void HUD::setCrossHairOffset(const glm::vec2& planeOffset) {

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

