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

    const CameraHead& cameraHead() const;

    void setHeadOrientation(const glm::quat& orientation);

    void followWorldObject(WorldObject* m_followWorldObject);

    void update(float deltaSec);


protected:
    std::unique_ptr<CameraHead> m_cameraHead;
    std::unique_ptr<CameraFollowHelper> m_followHelper;
};

