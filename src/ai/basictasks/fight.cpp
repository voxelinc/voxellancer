#include "fight.h"

Fight::Fight(Ship& ship, std::list<std::shared_ptr<WorldObjectHandle>> targets) :
BasicTask(ship),
m_targets(targets)
{
    m_state = 0;
    m_maxFireDistance = m_ship.maxAimDistance();
    m_maxRocketDistance = 200.0f;
    m_minEnemyDistance = 100.0f;
    m_stateChanged = false;
}

void Fight::update(float deltaSec) {
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
                m_ship.boardComputer()->moveTo(m_primaryTarget->transform().position(), m_minEnemyDistance);
            }
            m_ship.boardComputer()->shootBullet(m_targets);
            break;
        case ENGAGE:
            if (angleToTarget() > 45.0f) {
                m_ship.boardComputer()->moveTo(m_ship.transform().position() + glm::vec3(0, 0, -1)*m_ship.transform().orientation());
                m_ship.boardComputer()->rotateTo(m_primaryTarget->transform().position());
            } else {
                m_ship.boardComputer()->rotateTo(m_primaryTarget->transform().position());
                m_ship.boardComputer()->moveTo(m_primaryTarget->transform().position(), m_minEnemyDistance);
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

void Fight::updateTargets() {
    auto iterator = m_targets.begin();
    while (iterator != m_targets.end()) {
        if (!(*iterator)->get()) {
            m_targets.erase(iterator++);
        } else {
            iterator++;
        }
    }
    if (!m_targets.empty()) {
        m_primaryTarget = m_targets.front()->get();
    }
}


void Fight::addTargets(std::list<std::shared_ptr<WorldObjectHandle>> targets) {
    m_targets.insert(m_targets.end(), targets.begin(), targets.end());
}

void Fight::setTargets(std::list<std::shared_ptr<WorldObjectHandle>> targets) {
    m_targets = targets;
}

bool Fight::isInProgress() {
    return m_state != IDLE;
}

void Fight::updateState() {
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

float Fight::targetDistance() {
    return glm::length(m_ship.transform().position() - m_primaryTarget->transform().position()) - m_ship.minimalGridSphere().radius() * m_ship.transform.scale() - m_primaryTarget->minimalGridSphere().radius() * m_primaryTarget->transform.scale();
}

float Fight::pointDistance(glm::vec3 point) {
    return glm::length(m_ship.transform().position() - point) - m_ship.minimalGridSphere().radius() * m_ship.transform.scale();
}

glm::vec3 Fight::findRandomEvasionPoint() {
    glm::vec3 point = glm::vec3(RandFloat::rand(-0.25f, 0.25), RandFloat::rand(-0.25f, 0.25), -1);
    point *= 3 * m_minEnemyDistance;
    point = point * m_ship.transform().orientation();
    point += m_ship.transform().position();
    return point;
}

void Fight::setState(int newState) {
    m_stateChanged = true;
    m_state = newState;
}

float Fight::angleToTarget() {
    glm::vec3 shipDirection = glm::vec3(0, 0, -1);
    glm::vec3 targetDirection = glm::inverse(m_ship.transform().orientation()) * glm::normalize(m_primaryTarget->transform().position() - m_ship.transform().position());
    float angle = glm::acos(glm::clamp(glm::dot(glm::normalize(shipDirection), glm::normalize(targetDirection)), 0.0f, 1.0f));
    assert(std::isfinite(angle));
    return glm::degrees(angle);
}
