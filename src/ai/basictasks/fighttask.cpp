#include "fighttask.h"
#include "worldobject/ship.h"
#include "ai/boardcomputer.h"

#include "ai/basictasks/fighterfighttask.h"
#include "ai/basictasks/cruiserfighttask.h"


FightTask::FightTask(BoardComputer* boardComputer, const std::vector<Handle<WorldObject>>& targets) :
    AiTask(boardComputer)
{
    if (boardComputer->worldObject()->voxelCount() < 10000) { // better: WorldObjectType::BigShip?
        m_task.reset(new FighterFightTask(boardComputer, targets));
    } else {
        m_task.reset(new CruiserFightTask(boardComputer, targets));
    }
}

void FightTask::update(float deltaSec) {
    m_task->update(deltaSec);
}

std::vector<Handle<WorldObject>>& FightTask::targets() {
    return m_task->targets();
}

void FightTask::addTarget(const Handle<WorldObject>& target) {
    m_task->addTarget(target);
}

void FightTask::setTargets(const std::vector<Handle<WorldObject>>& targets) {
    m_task->setTargets(targets);
}

bool FightTask::isFinished() {
    return m_task->isFinished();
}