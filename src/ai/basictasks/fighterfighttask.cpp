#include "fighterfighttask.h"

#include "ai/boardcomputer.h"
#include "utils/geometryhelper.h"
#include "utils/safenormalize.h"
#include "utils/randfloat.h"
#include "voxel/voxelclusterbounds.h"
#include "worldobject/ship.h"


FighterFightTask::FighterFightTask(BoardComputer* boardComputer, const std::vector<Handle<WorldObject>>& targets) :
    FightTaskImplementation(boardComputer, targets)
{
    m_state = State::IDLE;
    m_maxFireDistance = 150.0f;
    m_maxRocketDistance = 200.0f;
    m_minEnemyDistance = 100.0f;
    m_stateChanged = false;
}

void FighterFightTask::update(float deltaSec) {
    updateTargets();
    updateState();

    WorldObject* worldObject = boardComputer()->worldObject();

    switch (m_state) {
        case State::IDLE:
            return;
        case State::APPROACH:
            if (angleToTarget() > 45.0f) {
                boardComputer()->rotateTo(m_primaryTarget->transform().position());
            } else {
                boardComputer()->rotateTo(m_primaryTarget->transform().position());
                boardComputer()->moveTo(m_primaryTarget->transform().position());
            }
            boardComputer()->shootBullet(m_targets);
            break;
        case State::ENGAGE:
            if (angleToTarget() > 45.0f) {
                boardComputer()->moveTo(worldObject->transform().position() + glm::vec3(0, 0, -1) * worldObject->transform().orientation());
                boardComputer()->rotateTo(m_primaryTarget->transform().position());
            } else {
                boardComputer()->rotateTo(m_primaryTarget->transform().position());
                boardComputer()->moveTo(m_primaryTarget->transform().position());
                if (angleToTarget() < 15.0f && targetDistance() < m_maxRocketDistance) {
                    boardComputer()->shootRockets(m_primaryTarget);
                }
            }
            if (targetDistance() < m_maxFireDistance) {
                boardComputer()->shootBullet(m_targets);
            }
            break;
        case State::EVADE:
            boardComputer()->rotateTo(m_positionBehindTarget);
            boardComputer()->moveTo(m_positionBehindTarget);
            boardComputer()->shootBullet(m_targets);
            break;
    }
}

bool FighterFightTask::isFinished() {
    return m_state == State::IDLE;
}

void FighterFightTask::updateState() {
    if (m_state != State::IDLE && m_targets.empty()) {
        setState(State::IDLE);
    }

    switch (m_state) {
        case State::IDLE:
            if (m_targets.empty()) {
                return;
            } else {
                setState(State::APPROACH);
            }
            break;
        case State::APPROACH:
            if (targetDistance() < m_maxFireDistance) {
                setState(State::ENGAGE);
            }
            break;
        case State::ENGAGE:
            if (targetDistance() < m_minEnemyDistance) {
                setState(State::EVADE);
                m_positionBehindTarget = findRandomEvasionPoint();
            }
            break;
        case State::EVADE:
            if (pointDistance(m_positionBehindTarget) < 20 && targetDistance() < m_minEnemyDistance) {
                m_positionBehindTarget = findRandomEvasionPoint();
            }
            if (pointDistance(m_positionBehindTarget) > 20)
                break;
            if (targetDistance() < m_minEnemyDistance) {
                break;
            }
            if (targetDistance() < m_maxFireDistance) {
                setState(State::ENGAGE);
            } else {
                setState(State::APPROACH);
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

float FighterFightTask::pointDistance(const glm::vec3& point) {
    WorldObject* worldObject = boardComputer()->worldObject();
    return glm::length(worldObject->transform().position() - point) - worldObject->bounds().minimalGridSphere().radius() * worldObject->transform().scale();
}

glm::vec3 FighterFightTask::findRandomEvasionPoint() {
    WorldObject* worldObject = boardComputer()->worldObject();
    glm::vec3 point = glm::vec3(RandFloat::rand(-0.25f, 0.25), RandFloat::rand(-0.25f, 0.25), -1);
    point *= 3 * m_minEnemyDistance;
    point = point * worldObject->transform().orientation();
    point += worldObject->transform().position();
    return point;
}

void FighterFightTask::setState(State newState) {
    m_stateChanged = true;
    m_state = newState;
}

float FighterFightTask::angleToTarget() {
    WorldObject* worldObject = boardComputer()->worldObject();
    glm::vec3 shipDirection = glm::vec3(0, 0, -1);
    glm::vec3 targetDirection = glm::inverse(worldObject->transform().orientation()) * safeNormalize(m_primaryTarget->transform().position() - worldObject->transform().position());
    float angle = GeometryHelper::angleBetween(shipDirection, targetDirection);
    return glm::degrees(angle);
}

