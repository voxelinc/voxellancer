#include "crosshair.h"

#include "camera/camerahead.h"
#include "camera/cameradolly.h"

#include "hud.h"


CrossHair::CrossHair(HUD* hud):
    Hudget(hud),
    m_crossHairVoxels(this)
{

}

glm::vec3 CrossHair::position() const {
    return m_hud->position() + orientation() * glm::vec3(0, 0, -m_hud->sphere().radius());
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

void CrossHair::update(float deltaSec) {

}

void CrossHair::draw() {
    m_crossHairVoxels.draw();
}

