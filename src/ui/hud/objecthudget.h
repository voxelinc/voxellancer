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

    virtual void onClick(int button) override;

    HUDObjectDelegate* objectDelegate();


protected:
    HUDObjectDelegate* m_objectDelegate;
    ObjectHudgetVoxels m_objectVoxels;
    ArrowHudgetVoxels m_arrowVoxels;

    bool m_targeted;
    void updateTargeted();

    bool m_insideFov;
    float m_fovy, m_fovx;

    bool isInsideFov();
    glm::vec3 closestPointInsideFov();

    void calculateOpeningAngle();

    void updateFov();
};

