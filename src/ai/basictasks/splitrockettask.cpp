#include "splitrockettask.h"

#include "equipment/weapons/splitrocket.h"
#include "ai/boardcomputer.h"
#include "utils/geometryhelper.h"
#include "utils/worldobjectgeometryhelper.h"

SplitRocketTask::SplitRocketTask(SplitRocket* rocket, BoardComputer* boardComputer, WorldObject* target) :
    DirectSuicideTask(boardComputer, target),
    m_flytime(0)
{
    assert(boardComputer->worldObject() == rocket); // alternative: create a Rocket::m_boardComputer accessor
    m_rocket = rocket;
}

void SplitRocketTask::update(float deltaSec) {
    DirectSuicideTask::update(deltaSec);
    m_flytime += deltaSec;
    if (m_flytime > 0.5f && m_target.valid()) {
        glm::vec3 requiredDirection = m_target->position() - m_rocket->position();
        glm::vec3 rocketDirection = m_rocket->orientation() * glm::vec3(0, 0, -1);

        if (GeometryHelper::angleBetween(requiredDirection, rocketDirection) <= m_rocket->splitAngle()
            && WorldObjectGeometryHelper::sphereToSphereDistance(m_rocket, m_target.get()) <= m_rocket->splitDistance()) {
            m_rocket->split();
        }
    }
}

