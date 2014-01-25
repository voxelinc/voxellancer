#include "cameradolly.h"


CameraDolly::CameraDolly():
    InertiaFollower(10.0f, 10.0f),
    m_cameraHead(this)
{
}

CameraHead& CameraDolly::cameraHead() {
    return m_cameraHead;
}

void CameraDolly::followWorldObject(WorldObject* followWorldObject) {
    m_followHelper.setTarget(followWorldObject);
}

void CameraDolly::update(float deltaSec) {
    WorldObject* followWorldObject = m_followHelper.target();

    if(followWorldObject) {
        follow(m_followHelper.followPosition(), followWorldObject->transform().orientation(), deltaSec);
    }
}

