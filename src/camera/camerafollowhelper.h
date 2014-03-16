#pragma once

#include <glm/glm.hpp>

#include "utils/handle/handle.h"


class WorldObject;

class CameraFollowHelper {
public:
    CameraFollowHelper();

    WorldObject* target();
    void setTarget(WorldObject* target);

    glm::vec3 followPosition();


protected:
    Handle<WorldObject> m_target;
};


