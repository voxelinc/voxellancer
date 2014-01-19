#include "camerahead.h"

#include <GLFW/glfw3.h>

#include "cameradolly.h"


CameraHead::CameraHead(CameraDolly* cameraDolly):
    m_cameraDolly(cameraDolly)
{

}

CameraDolly* CameraHead::cameraDolly() {
    return m_cameraDolly;
}

const glm::quat& CameraHead::relativeOrientation() const {
    return m_relativeOrientation;
}

void CameraHead::setRelativeOrientation(const glm::quat& relativeOrientation) {
    m_relativeOrientation = relativeOrientation;
}

float CameraHead::fovy() const {
    return m_eyes.front()->camera().fovy();
}

float CameraHead::nearZ() const {
    return m_eyes.front()->camera().zNear();
}

float CameraHead::farZ() const {
    return m_eyes.front()->camera().zFar();
}

float CameraHead::aspectRatio() const {
    return m_eyes.front()->camera().aspectRatio();
}

glm::vec3 CameraHead::position() const {
    return m_cameraDolly->position();
}

glm::quat CameraHead::orientation() const {
    return m_cameraDolly->orientation() * m_relativeOrientation;
}



