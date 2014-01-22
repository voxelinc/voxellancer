#include "crosshair.h"

#include "camera/camerahead.h"
#include "camera/cameradolly.h"

#include "hud.h"


CrossHair::CrossHair(HUD* hud):
    m_hud(hud),
    m_crossHairVoxels(this)
{

}

HUD* CrossHair::hud() {
    return m_hud;
}

glm::vec3 CrossHair::position() const {
    return m_hud->position() + m_hud->orientation() * m_positionOffset;
}

glm::quat CrossHair::orientation() const {
    return m_hud->orientation() * m_orientationOffset;
}

const glm::quat& CrossHair::orientationOffset() const {
    return m_orientationOffset;
}

void CrossHair::setOrientationOffset(const glm::quat& orientationOffset) {
    m_orientationOffset = orientationOffset;
}

const glm::vec3& CrossHair::positionOffset() const {
    return m_positionOffset;
}

void CrossHair::setPositionOffset(const glm::vec3& positionOffset) {
    m_positionOffset = positionOffset;
}

void CrossHair::update(float deltaSec) {

}

void CrossHair::draw() {
    m_crossHairVoxels.draw();
}

