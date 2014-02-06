#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "hudget.h"
#include "arrowhudgetvoxels.h"


class HUDObjectDelegate;

class ArrowHudget: public Hudget {
public:
    ArrowHudget(HUD* hud, HUDObjectDelegate* objectDelegate);

    virtual void update(float deltaSec) override;
    virtual void draw() override;


protected:
    HUDObjectDelegate* m_objectDelegate;
    ArrowHudgetVoxels m_voxels;

    //void calculateOpeningAngle();
};

