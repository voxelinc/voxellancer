#include "cruiserfighttask.h"
#include "utils/randfloat.h"
#include "worldobject/ship.h"
#include "ai/boardcomputer.h"
#include "voxel/voxelclusterbounds.h"
#include "utils/geometryhelper.h"


CruiserFightTask::CruiserFightTask(BoardComputer* boardComputer, const std::vector<Handle<WorldObject>>& targets) :
    FightTaskImplementation(boardComputer, targets)
{
    m_state = State::IDLE;
    m_maxFireDistance = 250.0f;
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
            boardComputer()->shootRockets(m_primaryTarget->handle());
        }

        if (anyTargetDistance() < m_maxFireDistance) {
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
    WorldObject* closestTarget = GeometryHelper::closestObject(*worldObject, &m_targets);
    
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