#include "fighttask.h"
#include "utils/randfloat.h"
#include "worldobject/ship.h"

FightTask::FightTask(Ship& ship, const std::vector<Handle<WorldObject>>& targets) :
    BasicTask(ship),
    m_targets(targets)
{
    m_state = 0;
    m_maxFireDistance = 150.0f;
    m_maxRocketDistance = 200.0f;
    m_minEnemyDistance = 100.0f;
    m_stateChanged = false;
}

void FightTask::update(float deltaSec) {
    updateTargets();
    updateState();

    switch (m_state) {
        case IDLE:
            return;
        case APPROACH:
            if (angleToTarget() > 45.0f) {
                m_ship.boardComputer();
                m_ship.boardComputer()->rotateTo(m_primaryTarget->transform().position());
            } else {
                m_ship.boardComputer()->rotateTo(m_primaryTarget->transform().position());
                m_ship.boardComputer()->moveTo(m_primaryTarget->transform().position());
            }
            m_ship.boardComputer()->shootBullet(m_targets);
            break;
        case ENGAGE:
            if (angleToTarget() > 45.0f) {
                m_ship.boardComputer()->moveTo(m_ship.transform().position() + glm::vec3(0, 0, -1)*m_ship.transform().orientation());
                m_ship.boardComputer()->rotateTo(m_primaryTarget->transform().position());
            } else {
                m_ship.boardComputer()->rotateTo(m_primaryTarget->transform().position());
                m_ship.boardComputer()->moveTo(m_primaryTarget->transform().position());
                if (angleToTarget() < 15.0f && targetDistance() < m_maxRocketDistance) {
                    m_ship.boardComputer()->shootRockets(m_primaryTarget->handle());
                }
            }
            if (targetDistance() < m_maxFireDistance) {
                m_ship.boardComputer()->shootBullet(m_targets);
            }
            break;
        case EVADE:
            m_ship.boardComputer()->rotateTo(m_positionBehindTarget);
            m_ship.boardComputer()->moveTo(m_positionBehindTarget);
            m_ship.boardComputer()->shootBullet(m_targets);
            break;
    }
}

void FightTask::updateTargets() {
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
    }
}


void FightTask::addTargets(const std::vector<Handle<WorldObject>>& targets) {
    m_targets.insert(m_targets.end(), targets.begin(), targets.end());
}

void FightTask::setTargets(const std::vector<Handle<WorldObject>>& targets) {
    m_targets = targets;
}

bool FightTask::isInProgress() {
    return m_state != IDLE;
}

void FightTask::updateState() {
    switch (m_state) {
        case IDLE:
            if (m_targets.empty()) {
                return;
            } else {
                setState(APPROACH);
            }
            break;
        case APPROACH:
            if (targetDistance() < m_maxFireDistance) {
                setState(ENGAGE);
            }
            break;
        case ENGAGE:
            if (targetDistance() < m_minEnemyDistance) {
                setState(EVADE);
                m_positionBehindTarget = findRandomEvasionPoint();
            }
            break;
        case EVADE:
            if (pointDistance(m_positionBehindTarget) < 20 && targetDistance() < m_minEnemyDistance) {
                m_positionBehindTarget = findRandomEvasionPoint();
            }
            if (pointDistance(m_positionBehindTarget) > 20)
                break;
            if (targetDistance() < m_minEnemyDistance) {
                break;
            }
            if (targetDistance() < m_maxFireDistance) {
                setState(ENGAGE);
            } else {
                setState(APPROACH);
            }
            break;
        default:
            assert(false);
            return;
    }

    if (m_state > 0 && m_targets.empty()) {
        setState(IDLE);
    }

    if (m_stateChanged) {
        m_stateChanged = false;
        updateState();
    }
}

float FightTask::targetDistance() {
    return glm::length(m_ship.transform().position() - m_primaryTarget->transform().position()) - m_ship.bounds().minimalGridSphere().radius() * m_ship.transform().scale() - m_primaryTarget->bounds().minimalGridSphere().radius() * m_primaryTarget->transform().scale();
}

float FightTask::pointDistance(glm::vec3 point) {
    return glm::length(m_ship.transform().position() - point) - m_ship.bounds().minimalGridSphere().radius() * m_ship.transform().scale();
}

glm::vec3 FightTask::findRandomEvasionPoint() {
    glm::vec3 point = glm::vec3(RandFloat::rand(-0.25f, 0.25), RandFloat::rand(-0.25f, 0.25), -1);
    point *= 3 * m_minEnemyDistance;
    point = point * m_ship.transform().orientation();
    point += m_ship.transform().position();
    return point;
}

void FightTask::setState(int newState) {
    m_stateChanged = true;
    m_state = newState;
}

float FightTask::angleToTarget() {
    glm::vec3 shipDirection = glm::vec3(0, 0, -1);
    glm::vec3 targetDirection = glm::inverse(m_ship.transform().orientation()) * glm::normalize(m_primaryTarget->transform().position() - m_ship.transform().position());
    float angle = glm::acos(glm::clamp(glm::dot(glm::normalize(shipDirection), glm::normalize(targetDirection)), 0.0f, 1.0f));
    assert(std::isfinite(angle));
    return glm::degrees(angle);
}
