#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "hudget.h"
#include "objectdelegatehudgetvoxels.h"


class HUDObjectDelegate;

class ObjectDelegateHudget: public Hudget {
public:
    ObjectDelegateHudget(HUD* hud, HUDObjectDelegate* objectDelegate);

    glm::vec3 position() const;
    glm::quat orientation() const;


    void update(float deltaSec);
    void draw();


protected:
    HUDObjectDelegate* m_objectDelegate;
    ObjectDelegateHudgetVoxels m_voxels;
    glm::quat m_orientationOffset;
};

