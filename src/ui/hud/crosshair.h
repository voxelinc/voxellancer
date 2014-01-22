#pragma once

#include <glm/gtc/quaternion.hpp>

#include "camera/camera.h"

#include "utils/inertiafollower.h"

#include "crosshairvoxels.h"


class HUD;
class CameraHead;

class CrossHair {
public:
    CrossHair(HUD* hud);

    HUD* hud();

    glm::vec3 position() const;
    glm::quat orientation() const;

    const glm::quat& orientationOffset() const;
    void setOrientationOffset(const glm::quat& orientationOffset);

    const glm::vec3& positionOffset() const;
    void setPositionOffset(const glm::vec3& positionOffset);

    void update(float deltaSec);
    void draw();


protected:
    HUD* m_hud;
    glm::quat m_orientationOffset;
    glm::vec3 m_positionOffset;
    CrossHairVoxels m_crossHairVoxels;
};
