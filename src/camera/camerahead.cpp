#include "camerahead.h"

#include <GL/glew.h>
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

glm::vec3 CameraHead::position() const {
    return m_cameraDolly->position();
}

glm::quat CameraHead::orientation() const {
    return m_cameraDolly->orientation() * m_relativeOrientation;
}



