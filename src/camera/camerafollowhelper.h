#pragma once

#include <glm/glm.hpp>

#include "worldobject/worldobject.h"


class CameraFollowHelper {
public:
    CameraFollowHelper(WorldObject* worldObject);

    glm::vec3 position();


protected:
    WorldObject* m_worldObject;
};
