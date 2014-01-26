#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "hudget.h"
#include "objecthudgetvoxels.h"


class HUDObjectDelegate;

class ObjectHudget: public Hudget {
public:
    ObjectHudget(HUD* hud, HUDObjectDelegate* objectDelegate);

    virtual glm::vec3 position() const override;
    virtual glm::quat orientation() const override;

    void update(float deltaSec);
    void draw();


protected:
    HUDObjectDelegate* m_objectDelegate;
    ObjectHudgetVoxels m_voxels;
    glm::quat m_orientationOffset;


    void calculateOpeningAngle();
};

