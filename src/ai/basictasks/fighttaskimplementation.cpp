#include "fighttaskimplementation.h"

#include "ai/boardcomputer.h"
#include "utils/worldobjectgeometryhelper.h"
#include "worldobject/worldobject.h"
#include "worldobject/worldobjectcomponents.h"
#include "worldobject/helper/componentsinfo.h"


FightTaskImplementation::FightTaskImplementation(BoardComputer* boardComputer, const std::vector<Handle<WorldObject>>& targets) :
    AiTask(boardComputer),
    m_targets(targets),
    m_primaryTarget(nullptr)
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

void FightTaskImplementation::updateTargets() {
    auto iterator = m_targets.begin();
    while (iterator != m_targets.end()) {
        if (!iterator->get()) {
            iterator = m_targets.erase(iterator);
        } else {
            iterator++;
        }
    }

    if (!m_targets.empty()) {
        m_primaryTarget = m_targets.front().get();
    } else {
        m_primaryTarget = nullptr;
    }
}

float FightTaskImplementation::targetDistance() {
    return WorldObjectGeometryHelper::sphereToSphereDistance(boardComputer()->worldObject(), m_primaryTarget);
}

const ComponentsInfo& FightTaskImplementation::componentsInfo() {
    return boardComputer()->worldObject()->components().componentsInfo();
}

