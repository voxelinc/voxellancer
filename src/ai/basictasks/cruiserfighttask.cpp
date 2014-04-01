#include "cruiserfighttask.h"
#include "utils/randfloat.h"
#include "worldobject/ship.h"
#include "ai/boardcomputer.h"
#include "voxel/voxelclusterbounds.h"
#include "utils/geometryhelper.h"


CruiserFightTask::CruiserFightTask(BoardComputer* boardComputer, const std::vector<Handle<WorldObject>>& targets) :
    FightTaskImplementation(boardComputer, targets),
    m_primaryTarget(nullptr)
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

void CruiserFightTask::updateTargets() {
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

float CruiserFightTask::targetDistance() {
    WorldObject* worldObject = boardComputer()->worldObject();
    return glm::length(worldObject->transform().position() - m_primaryTarget->transform().position())
        - worldObject->bounds().minimalGridSphere().radius() * worldObject->transform().scale()
        - m_primaryTarget->bounds().minimalGridSphere().radius() * m_primaryTarget->transform().scale();
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

float CruiserFightTask::angleToTarget() {
    WorldObject* worldObject = boardComputer()->worldObject();
    glm::vec3 shipDirection = glm::vec3(0, 0, -1);
    glm::vec3 targetDirection = glm::inverse(worldObject->transform().orientation()) * glm::normalize(m_primaryTarget->transform().position() - worldObject->transform().position());
    float angle = glm::acos(glm::clamp(glm::dot(glm::normalize(shipDirection), glm::normalize(targetDirection)), 0.0f, 1.0f));
    assert(std::isfinite(angle));
    return glm::degrees(angle);
}
