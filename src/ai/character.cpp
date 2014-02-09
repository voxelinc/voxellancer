#include "character.h"

#include "ai/aitask.h"
#include "worldobject/ship.h"
#include "ai/squadlogic.h"
#include "ai/squad.h"
#include "ai/aigrouptask.h"

Character::Character(Ship& ship) :
    m_ship(ship),
    m_task(nullptr)
{
}

void Character::setTask(std::shared_ptr<AiTask> task) {
    m_task = task;
}

std::shared_ptr<AiTask> Character::task() {
    return m_task;
}

void Character::update(float deltaSec) {
    if (m_ship.squadLogic()->isSquadLeader()) {
        m_ship.squadLogic()->squad()->task()->update(deltaSec);
    }
    if (m_task.get()) {
        m_task->update(deltaSec);
    }
}