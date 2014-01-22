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
    return m_hud->position() + orientation() * glm::vec3(0, 0 , -m_hud->sphere().radius());
}

glm::quat CrossHair::orientation() const {
    return m_hud->orientation() * m_directionOffset;
}

const glm::quat& CrossHair::directionOffset() const {
    return m_directionOffset;
}

void CrossHair::setDirectionOffset(const glm::quat& directionOffset) {
    m_directionOffset = directionOffset;
}

void CrossHair::update(float deltaSec) {

}

void CrossHair::draw() {
    m_crossHairVoxels.draw();
}

