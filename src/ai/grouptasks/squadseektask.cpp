#include "squadseektask.h"

#include <glow/logging.h>

#include "ai/basictasks/formationmembertask.h"
#include "ai/character.h"
#include "ai/squad.h"

#include "utils/randvec3.h"

#include "worldobject/ship.h"


SquadSeekTask::SquadSeekTask(Squad& squad, AiGroupTask* parent):
    AiGroupTask(squad, parent)
{

}

SquadSeekTask::~SquadSeekTask() = default;

void SquadSeekTask::update(float deltaSec) {
    if (!squad().leader()) {
        return;
    }

    float distanceToTargetPoint = glm::length(m_leaderFlyTask->targetPoint() - squad().leader()->transform().position());

    if (distanceToTargetPoint < 20.0f) {
        m_leaderFlyTask->setTargetPoint(newTargetPoint());
    }
}

void SquadSeekTask::onEntered() {
    for (Ship* ship : squad().members()) {
        ship->character()->setTask(std::make_shared<FormationMemberTask>(*ship));
    }
    if (squad().leader()) {
        m_leaderFlyTask = std::make_shared<FlyToTask>(squad().leader()->boardComputer());
        squad().leader()->character()->setTask(m_leaderFlyTask);
    }

    m_leaderFlyTask->setTargetPoint(newTargetPoint());
}

glm::vec3 SquadSeekTask::newTargetPoint() const {
    return RandVec3::rand(glm::vec3(-500.0f, -100.0f, -500.0f), glm::vec3(500.0f, 100.0f, 500.0f));
}

