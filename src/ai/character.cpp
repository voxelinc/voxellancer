#include "character.h"

#include "ai/aigrouptask.h"
#include "ai/aitask.h"
#include "ai/squad.h"
#include "ai/squadlogic.h"

#include "worldobject/ship.h"


Character::Character(Ship& ship, Faction& faction):
    m_ship(ship),
    m_faction(&faction),
    m_task(nullptr)
{
}

Faction& Character::faction() {
    return *m_faction;
}

void Character::setFaction(Faction& faction) {
    m_faction = &faction;
}

void Character::setTask(std::shared_ptr<AiTask> task) {
    m_task = task;
}

std::shared_ptr<AiTask> Character::task() {
    return m_task;
}

void Character::update(float deltaSec) {
    if (m_ship.squadLogic()->isSquadLeader() && m_ship.squadLogic()->squad()->task().get()) {
        m_ship.squadLogic()->squad()->task()->update(deltaSec);
    }
    if (m_task.get()) {
        m_task->update(deltaSec);
    }
}

