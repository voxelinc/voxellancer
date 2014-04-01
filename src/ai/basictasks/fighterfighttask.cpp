#include "fighterfighttask.h"
#include "utils/randfloat.h"
#include "worldobject/ship.h"
#include "ai/boardcomputer.h"
#include "voxel/voxelclusterbounds.h"


FighterFightTask::FighterFightTask(BoardComputer* boardComputer, const std::vector<Handle<WorldObject>>& targets) :
    FightTaskImplementation(boardComputer, targets),
    m_primaryTarget(nullptr)
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
                    boardComputer()->shootRockets(m_primaryTarget->handle());
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

void FighterFightTask::updateTargets() {
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

float FighterFightTask::targetDistance() {
    WorldObject* worldObject = boardComputer()->worldObject();
    return glm::length(worldObject->transform().position() - m_primaryTarget->transform().position()) 
                        - worldObject->bounds().minimalGridSphere().radius() * worldObject->transform().scale() 
                        - m_primaryTarget->bounds().minimalGridSphere().radius() * m_primaryTarget->transform().scale();
}

float FighterFightTask::pointDistance(glm::vec3 point) {
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
    glm::vec3 targetDirection = glm::inverse(worldObject->transform().orientation()) * glm::normalize(m_primaryTarget->transform().position() - worldObject->transform().position());
    float angle = glm::acos(glm::clamp(glm::dot(glm::normalize(shipDirection), glm::normalize(targetDirection)), 0.0f, 1.0f));
    assert(std::isfinite(angle));
    return glm::degrees(angle);
}
