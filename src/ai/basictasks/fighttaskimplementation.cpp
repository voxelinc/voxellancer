#include "fighttaskimplementation.h"


FightTaskImplementation::FightTaskImplementation(BoardComputer* boardComputer, const std::vector<Handle<WorldObject>>& targets) :
    AiTask(boardComputer),
    m_targets(targets)
{
}

std::vector<Handle<WorldObject>>& FightTaskImplementation::targets() {
    return m_targets;
}

void FightTaskImplementation::addTarget(const Handle<WorldObject>& target) {
    m_targets.push_back(target);
}

void FightTaskImplementation::setTargets(const std::vector<Handle<WorldObject>>& targets) {
    m_targets = targets;
}
