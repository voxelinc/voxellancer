#pragma once

#include <glm/gtc/quaternion.hpp>

#include "utils/inertiafollower.h"

#include "crosshairvoxels.h"


class CameraHead;

class CrossHair: public InertiaFollower {
public:
    CrossHair(CameraHead* cameraHead);

    const glm::quat& directionOffset() const;
    void setDirectionOffset(const glm::quat& directionOffset);

    void update(float deltaSec);
    void draw();


protected:
    CameraHead* m_cameraHead;
    glm::quat m_directionOffset;
    CrossHairVoxels m_crossHairVoxels;
};
