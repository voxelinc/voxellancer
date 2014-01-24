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

    const glm::quat& directionOffset() const;
    void setDirectionOffset(const glm::quat& directionOffset);

    void update(float deltaSec);
    void draw();


protected:
    HUD* m_hud;
    glm::quat m_directionOffset;
    CrossHairVoxels m_crossHairVoxels;
};
