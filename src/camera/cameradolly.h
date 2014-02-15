#pragma once

#include "utils/inertiafollower.h"
#include "camerahead.h"
#include "camerafollowhelper.h"

class WorldObject;

class CameraDolly: public InertiaFollower {
public:
    CameraDolly();

    const CameraHead& cameraHead() const;

    void followWorldObject(WorldObject* m_followWorldObject);

    void update(float deltaSec);


protected:
    CameraHead m_cameraHead;
    CameraFollowHelper m_followHelper;
};

