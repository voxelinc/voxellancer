#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "hudget.h"
#include "objecthudgetvoxels.h"


class HUDObjectDelegate;

class ObjectHudget: public Hudget {
public:
    ObjectHudget(HUD* hud, HUDObjectDelegate* objectDelegate);

    bool isTarget() const;

    virtual void update(float deltaSec) override;
    virtual void draw() override;


protected:
    HUDObjectDelegate* m_objectDelegate;
    ObjectHudgetVoxels m_voxels;

    void calculateOpeningAngle();
};

