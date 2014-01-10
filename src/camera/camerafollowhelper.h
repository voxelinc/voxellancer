#pragma once

#include <glm/glm.hpp>

#include "worldobject/worldobject.h"


class CameraFollowHelper {
public:
    CameraFollowHelper(WorldObject* worldObject);

    glm::vec3 followPosition();


protected:
    WorldObject* m_worldObject;
};
