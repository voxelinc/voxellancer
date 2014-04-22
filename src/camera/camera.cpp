#include "camera.h"

#include <glow/logging.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include <glm/gtx/transform.hpp>


Camera::Camera(int viewportWidth, int viewportHeight)
{
    setViewport(viewportWidth, viewportHeight);

    setFovy(glm::radians(60.0f));

    setZNear(1.0f);
    setZFar(10000.0f);
}

glm::quat Camera::orientation() const {
    glm::quat q = glm::quat(glm::lookAt(center(), (eye()), up()));

    glm::vec3 e = glm::eulerAngles(q);
    glow::debug() << e << " vs " << glm::eulerAngles(m_orientation);

    return q;
}

void Camera::setOrientation(const glm::quat& orientation) {
    glowutils::Camera::setUp(orientation * glm::vec3(0, 1, 0));
    glowutils::Camera::setCenter(eye() + orientation * glm::vec3(0, 0, -1));
    m_orientation = orientation;
}

