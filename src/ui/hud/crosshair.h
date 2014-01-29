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

    /*
        True if the left mousebutton or the firebutton in the gamepad
        is pressed
    */
    bool actionActive() const;
    void setActionActive(bool actionActive);

    virtual void update(float deltaSec) override;
    virtual void draw() override;


protected:
    bool m_actionActive;
    CrossHairVoxels m_voxels;
};

