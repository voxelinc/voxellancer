#include "fighttaskimplementation.h"

#include "ai/boardcomputer.h"
#include "worldobject/worldobject.h"
#include "voxel/voxelclusterbounds.h"

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
    WorldObject* worldObject = boardComputer()->worldObject();
    return glm::length(worldObject->transform().position() - m_primaryTarget->transform().position())
        - worldObject->bounds().minimalGridSphere().radius() * worldObject->transform().scale()
        - m_primaryTarget->bounds().minimalGridSphere().radius() * m_primaryTarget->transform().scale();
}