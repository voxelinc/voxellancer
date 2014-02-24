#pragma once

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "hudget.h"

class ObjectHudgetVoxels;
class HUDObjectDelegate;

class ObjectHudget: public Hudget {
public:
    ObjectHudget(HUD* hud, HUDObjectDelegate* objectDelegate);
    virtual ~ObjectHudget();

    bool isTarget() const;

    virtual void update(float deltaSec) override;
    virtual void draw() override;


protected:
    HUDObjectDelegate* m_objectDelegate;
    std::unique_ptr<ObjectHudgetVoxels> m_voxels;

    void calculateOpeningAngle();
};

