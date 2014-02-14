#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "hudget.h"
#include "objecthudgetvoxels.h"
#include "arrowhudgetvoxels.h"


class HUDObjectDelegate;

class ObjectHudget: public Hudget {
public:
    ObjectHudget(HUD* hud, HUDObjectDelegate* objectDelegate);

    virtual void update(float deltaSec) override;
    virtual void draw() override;

    virtual bool isAt(const Ray& ray) const override;

    HUDObjectDelegate* objectDelegate();

    void setTargeted(bool targeted);
    bool isTargeted();


protected:
    HUDObjectDelegate* m_objectDelegate;
    ObjectHudgetVoxels m_objectVoxels;
    ArrowHudgetVoxels m_arrowVoxels;

    float fovy, fovx;

    bool isInsideFov();
    glm::vec3 closestPointInsideFov();

    void calculateOpeningAngle();

    bool m_targeted;
    bool m_insideFov;
};

