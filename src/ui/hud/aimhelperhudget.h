#pragma once

#include <glm/glm.hpp>

#include "aimhelperhudgetvoxels.h"
#include "hudget.h"


class HUD;

/*
    Hudget drawn where player-bullets and target
    will collide i.e. not actually on the hud-sphere but
    in the world
*/
class AimHelperHudget: public Hudget {
public:
    AimHelperHudget(HUD* hud);

    virtual glm::vec3 position() const override;
    virtual glm::quat orientation() const override;

    virtual void update(float deltaSec) override;
    virtual void draw();


protected:
    AimHelperHudgetVoxels m_voxels;
    glm::vec3 m_position;


    float bulletSpeed();
};

