#include "cameradolly.h"

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "camerafollowhelper.h"

#include "game.h"


CameraDolly::CameraDolly(Game* game):
    Follower(10.0f, 360.0f),
    m_game(game),
    m_cameraHead(this)
{
}

Game* CameraDolly::game() {
    return m_game;
}

void CameraDolly::setFollowObject(WorldObject* m_followWorldObject) {
    m_followWorldObjectHandle = m_followWorldObject->handle();
}

void CameraDolly::update(float deltaSec) {
    WorldObject* followWorldObject = m_followWorldObjectHandle->get();

    if(followWorldObject) {
        CameraFollowHelper followHelper(followWorldObject);
        follow(followHelper.position(), glm::eulerAngles(followWorldObject->transform().orientation()), deltaSec);
    }
    m_cameraHead.update(deltaSec);
}

void CameraDolly::draw() {
    m_cameraHead.draw();
}

