#include "camera.h"

#include <glm/gtx/transform.hpp>


Camera::Camera(int viewportWidth, int viewportHeight)
{
    setViewport(viewportWidth, viewportHeight);

    setFovy(glm::radians(60.0f));

    setZNear(1.0f);
    setZFar(10000.0f);
}

glm::quat Camera::orientation() const {
    return m_orientation;
}

void Camera::setOrientation(const glm::quat& orientation) {
    setUp(orientation * glm::vec3(0, 1, 0));
    setCenter(eye() + orientation * glm::vec3(0, 0, -1));
    m_orientation = orientation;
}

