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

    /**
     * Can't be set, orientation()/setOrientation() does their job.
     */
    void setCenter(const glm::vec3 & center) = delete;
    void setUp(const glm::vec3 & up) = delete;

    glm::quat orientation() const;
    void setOrientation(const glm::quat& orientation);


protected:
    glm::quat m_orientation;
};

