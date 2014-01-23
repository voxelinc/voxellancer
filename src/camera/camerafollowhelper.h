#pragma once

#include "worldobject/worldobject.h"
#include "worldobject/worldobjecthandle.h"


class CameraFollowHelper {
public:
    CameraFollowHelper();

    WorldObject* target();
    void setTarget(WorldObject* target);

    glm::vec3 followPosition();


protected:
    std::shared_ptr<WorldObjectHandle> m_target;
};


