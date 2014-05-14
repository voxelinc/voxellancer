#pragma once

#include <memory>

#include <glm/gtc/quaternion.hpp>

#include "hudget.h"


class HUD;
class CameraHead;
class CrossHairVoxels;

class CrossHair: public Hudget {
public:
    CrossHair(HUD* hud);
    virtual ~CrossHair();

    /**
     * True if the left mousebutton or the firebutton in the gamepad
     * is pressed
     */
    bool actionActive() const;
    void setActionActive(bool actionActive);

    virtual void update(float deltaSec) override;
    virtual void draw() override;


protected:
    bool m_actionActive;
    std::unique_ptr<CrossHairVoxels> m_voxels;
};

