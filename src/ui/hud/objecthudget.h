#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "hudget.h"
#include "objecthudgetvoxels.h"


class HUDObjectDelegate;

class ObjectHudget: public Hudget {
public:
    ObjectHudget(HUD* hud, HUDObjectDelegate* objectDelegate);

    virtual void update(float deltaSec) override;
    virtual void draw() override;

    virtual void onClick();

    virtual bool isAt(const Ray& ray) const override;

    HUDObjectDelegate* objectDelegate();


protected:
    HUDObjectDelegate* m_objectDelegate;
    ObjectHudgetVoxels m_voxels;

    void calculateOpeningAngle();
};

