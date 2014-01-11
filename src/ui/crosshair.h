#pragma once

#include <glm/gtc/quaternion.hpp>

#include "utils/inertiafollower.h"

#include "crosshairvoxels.h"


class CameraHead;

class CrossHair {
public:
    CrossHair(CameraHead* cameraHead);

    CameraHead* cameraHead();

    glm::vec3 position() const;
    const glm::quat& orientation() const;

    float distanceToBase() const;

    const glm::quat& directionOffset() const;
    void setDirectionOffset(const glm::quat& directionOffset);

    void update(float deltaSec);
    void draw();


protected:
    CameraHead* m_cameraHead;
    InertiaFollower m_base;
    float m_distanceToBase;
    glm::quat m_directionOffset;
    CrossHairVoxels m_crossHairVoxels;
};
