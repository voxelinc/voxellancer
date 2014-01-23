#pragma once


#include "utils/inertiafollower.h"
#include "camerahead.h"
#include "camerafollowhelper.h"

class WorldObject;
class WorldObjectHandle;

class CameraDolly: public InertiaFollower {
public:
    CameraDolly();

    CameraHead& cameraHead();

    void followWorldObject(WorldObject* m_followWorldObject);

    void update(float deltaSec);


protected:
    CameraHead m_cameraHead;
    CameraFollowHelper m_followHelper;
};

