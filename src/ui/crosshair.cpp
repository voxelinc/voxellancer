#include "crosshair.h"

#include "camera/camerahead.h"


CrossHair::CrossHair(CameraHead* cameraHead):
    m_cameraHead(cameraHead),
    m_base(45.0f, 45.0f),
    m_crossHairVoxels(this),
    m_distanceToBase(5.0f)
{

}

CameraHead* CrossHair::cameraHead() {
    return m_cameraHead;
}

glm::vec3 CrossHair::position() const {
    return m_base.position() + m_base.orientation() * glm::vec3(0, 0 , -m_distanceToBase);
}

const glm::quat& CrossHair::orientation() const {
    return m_base.orientation();
}

float CrossHair::distanceToBase() const {
    return m_distanceToBase;
}

const glm::quat& CrossHair::directionOffset() const {
    return m_directionOffset;
}

void CrossHair::setDirectionOffset(const glm::quat& directionOffset) {
    m_directionOffset = directionOffset;
}

void CrossHair::update(float deltaSec) {
    m_base.follow(m_cameraHead->position(), m_directionOffset * m_cameraHead->orientation(), deltaSec);
    m_crossHairVoxels.update(deltaSec);
}

void CrossHair::draw() {
    m_crossHairVoxels.draw();
}
