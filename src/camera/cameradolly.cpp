#include "cameradolly.h"

#include "worldobject/worldobject.h"
#include "camerafollowhelper.h"
#include "camerahead.h"


CameraDolly::CameraDolly():
    InertiaFollower(10.0f, 10.0f),
    m_cameraHead(new CameraHead(this)),
    m_followHelper(new CameraFollowHelper())
{
}

CameraDolly::~CameraDolly() = default;

CameraHead& CameraDolly::cameraHead() {
    return *m_cameraHead;
}

const CameraHead& CameraDolly::cameraHead() const {
    return *m_cameraHead;
}

void CameraDolly::followWorldObject(WorldObject* followWorldObject) {
    m_followHelper->setTarget(followWorldObject);
}

void CameraDolly::update(float deltaSec) {
    WorldObject* followWorldObject = m_followHelper->target();

    if(followWorldObject) {
        follow(m_followHelper->followPosition(), followWorldObject->transform().orientation(), deltaSec);
    }
}