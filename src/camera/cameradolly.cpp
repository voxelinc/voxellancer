#include "cameradolly.h"

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "camerafollowhelper.h"

#include "game.h"


CameraDolly::CameraDolly(Game* game):
    InertiaFollower(10.0f, 10.0f),
    m_game(game),
    m_cameraHead(this),
    m_followWorldObjectHandle(WorldObjectHandle::nullHandle())
{
}

Game* CameraDolly::game() {
    return m_game;
}

CameraHead& CameraDolly::cameraHead() {
    return m_cameraHead;
}

void CameraDolly::setFollowObject(WorldObject* m_followWorldObject) {
    m_followWorldObjectHandle = m_followWorldObject->handle();
}

void CameraDolly::update(float deltaSec) {
    WorldObject* followWorldObject = m_followWorldObjectHandle->get();

    if(followWorldObject) {
        CameraFollowHelper followHelper(followWorldObject);
        follow(followHelper.followPosition(), followWorldObject->transform().orientation(), deltaSec);
    }
    m_cameraHead.update(deltaSec);
}

void CameraDolly::draw() {
    m_cameraHead.draw();
}

