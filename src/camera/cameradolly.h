#pragma once

#include <memory>

#include "utils/inertiafollower.h"


class WorldObject;
class CameraHead;
class CameraFollowHelper;

class CameraDolly: public InertiaFollower {
public:
    CameraDolly();
    ~CameraDolly();

    CameraHead& cameraHead();
    const CameraHead& cameraHead() const;

    void followWorldObject(WorldObject* m_followWorldObject);

    void update(float deltaSec);

    void setInertia(float directional, float angular);

protected:
    std::unique_ptr<CameraHead> m_cameraHead;
    std::unique_ptr<CameraFollowHelper> m_followHelper;
};

