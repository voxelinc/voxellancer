#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "utils/inertiafollower.h"

#include "worldobject/worldobject.h"

#include "camerahead.h"


class Game;

class CameraDolly: public InertiaFollower {
public:
    CameraDolly();

    CameraHead& cameraHead();

    void followWorldObject(WorldObject* m_followWorldObject);

    void update(float deltaSec);


protected:
    CameraHead m_cameraHead;

    std::shared_ptr<WorldObjectHandle> m_followWorldObjectHandle;
};

