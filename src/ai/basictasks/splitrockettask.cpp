#include "splitrockettask.h"

#include "equipment/weapons/splitrocket.h"
#include "ai/boardcomputer.h"
#include "utils/geometryhelper.h"
#include "utils/worldobjectgeometryhelper.h"

SplitRocketTask::SplitRocketTask(SplitRocket* rocket, BoardComputer* boardComputer, WorldObject* target) :
    DirectSuicideTask(boardComputer, target)
{
    assert(boardComputer->worldObject() == rocket); // alternative: create a Rocket::m_boardComputer accessor
    m_rocket = rocket;
}

void SplitRocketTask::update(float deltaSec) {
    DirectSuicideTask::update(deltaSec);

    if (m_target.valid()) {
        glm::vec3 requiredDirection = m_target->position() - m_rocket->position();
        glm::vec3 rocketDirection = m_rocket->orientation() * glm::vec3(0, 0, -1);
        
        if (GeometryHelper::angleBetween(requiredDirection, rocketDirection) <= m_rocket->detonationFieldOfAim()
            && WorldObjectGeometryHelper::sphereToSphereDistance(m_rocket, m_target.get()) <= m_rocket->detonationDistance()) {
            m_rocket->detonate();
        }
    }
}


