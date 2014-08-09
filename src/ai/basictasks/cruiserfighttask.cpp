#include "cruiserfighttask.h"

#include "ai/boardcomputer.h"
#include "utils/randfloat.h"
#include "utils/worldobjectgeometryhelper.h"
#include "voxel/voxelclusterbounds.h"
#include "worldobject/ship.h"
#include "worldobject/helper/componentsinfo.h"


CruiserFightTask::CruiserFightTask(BoardComputer* boardComputer, const std::vector<Handle<WorldObject>>& targets) :
    FightTaskImplementation(boardComputer, targets)
{
    m_state = State::IDLE;
    m_maxRocketDistance = 150.0f;
    m_minEnemyDistance = 50.0f;
    m_stateChanged = false;
}

void CruiserFightTask::update(float deltaSec) {
    updateTargets();
    updateState();

    WorldObject* worldObject = boardComputer()->worldObject();

    switch (m_state) {
    case State::IDLE:
        return;
    case State::ENGAGE:
        boardComputer()->rotateTo(m_primaryTarget->transform().position());

        if (targetDistance() >= m_minEnemyDistance) {
            boardComputer()->moveTo(m_primaryTarget->transform().position());
        }

        if (targetDistance() < m_maxRocketDistance) {
            boardComputer()->shootRockets(m_primaryTarget);
        }

        if (anyTargetDistance() < componentsInfo().maxBulletRange()) {
            boardComputer()->shootBullet(m_targets);
        }
        break;
    }
}

bool CruiserFightTask::isFinished() {
    return m_state == State::IDLE;
}

void CruiserFightTask::updateState() {
    switch (m_state) {
    case State::IDLE:
        if (m_targets.empty()) {
            return;
        } else {
            setState(State::ENGAGE);
        }
        break;
    case State::ENGAGE:
        if (m_targets.empty()) {
            setState(State::IDLE);
        }
        break;
    default:
        assert(false);
        return;
    }

    if (m_stateChanged) {
        m_stateChanged = false;
        updateState();
    }
}

float CruiserFightTask::anyTargetDistance() {
    WorldObject* worldObject = boardComputer()->worldObject();
    WorldObject* closestTarget = WorldObjectGeometryHelper::closestObject(*worldObject, &m_targets);

    if (closestTarget) {
        return glm::length(worldObject->transform().position() - closestTarget->transform().position())
            - worldObject->bounds().minimalGridSphere().radius() * worldObject->transform().scale()
            - closestTarget->bounds().minimalGridSphere().radius() * closestTarget->transform().scale();
    } else {
        return std::numeric_limits<float>::infinity();
    }
}

void CruiserFightTask::setState(State newState) {
    m_stateChanged = true;
    m_state = newState;
}
