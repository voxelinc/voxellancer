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
        case idle:
            return;
        case approach:
            if (angleToTarget() > 45.0f) {
                m_ship.boardComputer()->rotateTo(m_primaryTarget->transform().position());
            } else {
                m_ship.boardComputer()->rotateTo(m_primaryTarget->transform().position());
                m_ship.boardComputer()->moveTo(m_primaryTarget->transform().position(), m_minEnemyDistance);
            }
            m_ship.boardComputer()->shootBullet(m_targets);
            break;
        case engage:
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
        case evade:
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
    if (m_state == idle) {
        return true;
    }
    return false;
}

void Fight::updateState() {
    switch (m_state) {
        case idle:
            if (m_targets.empty()) {
                return;
            } else {
                setState(approach);
            }
            break;
        case approach:
            if (targetDistance() < m_maxFireDistance) {
                setState(engage);
            }
            break;
        case engage:
            //printf("targetDistance: %f, minEnemyDistance: %f\n", targetDistance(), m_minEnemyDistance);
            if (targetDistance() < m_minEnemyDistance) {
                setState(evade);
                m_positionBehindTarget = findPositionBehindTarget();
            }
            break;
        case evade:
            if (pointDistance(m_positionBehindTarget) < 20 && targetDistance() < m_minEnemyDistance) {
                m_positionBehindTarget = findPositionBehindTarget();
            }
            if (pointDistance(m_positionBehindTarget) > 20)
                break;
            if (targetDistance() < m_minEnemyDistance) {
                break;
            }
            if (targetDistance() < m_maxFireDistance) {
                setState(engage);
            } else {
                setState(approach);
            }
            break;
        default:
            assert(false);
            return;
    }

    if (m_state > 0 && m_targets.empty()) {
        setState(idle);
    }

    if (m_stateChanged) {
        m_stateChanged = false;
        updateState();
    }
}

float Fight::targetDistance() {
    return glm::length(m_ship.transform().position() - m_primaryTarget->transform().position()) - m_ship.minimalGridSphere().radius() - m_primaryTarget->minimalGridSphere().radius();
}

float Fight::pointDistance(glm::vec3 point) {
    return glm::length(m_ship.transform().position() - point) - m_ship.minimalGridSphere().radius();
}

glm::vec3 Fight::findPositionBehindTarget() {
    float x = (rand() % 50 - 25) / 100.0f;
    float y = (rand() % 50 - 25) / 100.0f;
    glm::vec3 point = glm::vec3(x, y, -1);
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
