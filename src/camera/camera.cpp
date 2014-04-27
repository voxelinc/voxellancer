#include "camera.h"

#include <glow/logging.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include <glm/gtx/transform.hpp>


Camera::Camera(int viewportWidth, int viewportHeight):
    m_orientationDirty(true)
{
    setViewport(viewportWidth, viewportHeight);

    setFovy(glm::radians(60.0f));

    setZNear(1.0f);
    setZFar(10000.0f);
}

glm::quat Camera::orientation() const {
    if (m_orientationDirty) {
        const_cast<glm::quat&>(m_orientation) = glm::quat_cast(glm::inverse(view()));
        m_orientationDirty = false;
    }
    return m_orientation;
}

void Camera::setOrientation(const glm::quat& orientation) {
    glowutils::Camera::setUp(orientation * glm::vec3(0, 1, 0));
    glowutils::Camera::setCenter(eye() + orientation * glm::vec3(0, 0, -1));

    // changed() will be called anyway, no need to set m_orientationDirty = true
}

void Camera::changed() const {
    glowutils::Camera::changed();
    m_orientationDirty = true;
}

