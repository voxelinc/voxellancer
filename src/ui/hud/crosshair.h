#pragma once

#include <glm/gtc/quaternion.hpp>

#include "camera/camera.h"

#include "utils/inertiafollower.h"

#include "crosshairvoxels.h"
#include "hudget.h"


class HUD;
class CameraHead;

class CrossHair: public Hudget {
public:
    CrossHair(HUD* hud);

    virtual glm::vec3 position() const override;
    virtual glm::quat orientation() const override;

    const glm::quat& orientationOffset() const;
    void setOrientationOffset(const glm::quat& orientationOffset);

    void update(float deltaSec);
    void draw();


protected:
    glm::quat m_orientationOffset;
    CrossHairVoxels m_crossHairVoxels;
};

