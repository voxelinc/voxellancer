#pragma once

#include <glowutils/Camera.h>

#include <glm/glm.hpp>

#include "geometry/transform.h"


class Camera : public glowutils::Camera {
public:
    Camera(int viewportWidth, int viewportHeight);

    glm::quat orientation() const;
    void setOrientation(const glm::quat& orientation);

    virtual void changed() const override;


protected:
    mutable bool m_orientationDirty;
    glm::quat m_orientation;
};

