#pragma once

#include "aimhelperhudgetvoxels.h"
#include "hudget.h"


class HUD;

class AimHelperHudget: public Hudget {
public:
    AimHelperHudget(HUD* hud);

    virtual void update(float deltaSec) override;
    virtual void draw();


protected:
    AimHelperHudgetVoxels m_voxels;

    float bulletSpeed();
};

