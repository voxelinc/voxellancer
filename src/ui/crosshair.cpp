#include "crosshair.h"

#include "camera/camerahead.h"


CrossHair::CrossHair(CameraHead* cameraHead):
    InertiaFollower(45.0f, 45.0f),
    m_cameraHead(cameraHead),
    m_crossHairVoxels(this)
{

}

const glm::quat& CrossHair::directionOffset() const {
    return m_directionOffset;
}

void CrossHair::setDirectionOffset(const glm::quat& directionOffset) {
    m_directionOffset = directionOffset;
}

void CrossHair::update(float deltaSec) {
    InertiaFollower::follow(m_cameraHead->position(), m_directionOffset * m_cameraHead->orientation(), deltaSec);
    m_crossHairVoxels.update(deltaSec);
}

void CrossHair::draw() {
    m_crossHairVoxels.draw();
}
