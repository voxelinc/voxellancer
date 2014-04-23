#pragma once

#include <glowutils/Camera.h>

#include <glm/glm.hpp>

#include "geometry/transform.h"

/**
 *  Represents the camera. matrix thus is the view matrix for all other objects
 */
class Camera : public glowutils::Camera {
public:
    Camera(int viewportWidth, int viewportHeight);

    glm::quat orientation() const;
    void setOrientation(const glm::quat& orientation);


protected:
    glm::quat m_orientation;
};

