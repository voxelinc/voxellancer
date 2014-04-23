#include "camera.h"

#include <glm/gtx/transform.hpp>


Camera::Camera(int viewportWidth, int viewportHeight) {
    setViewport(viewportWidth, viewportHeight);

    setFovy(glm::radians(60.0f));

    setZNear(1.0f);
    setZFar(10000.0f);
}

glm::quat Camera::orientation() const {
    return glm::quat_cast(glm::inverse(view()));
}

void Camera::setOrientation(const glm::quat& orientation) {
    glowutils::Camera::setUp(orientation * glm::vec3(0, 1, 0));
    glowutils::Camera::setCenter(eye() + orientation * glm::vec3(0, 0, -1));
}

