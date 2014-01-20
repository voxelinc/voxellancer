#include "fight.h"

Fight::Fight(Ship& ship, std::list<std::shared_ptr<WorldObjectHandle>> targets) :
BasicTask(ship),
m_targets(targets)
{
    m_state = 0;
    m_maxFireDistance = m_ship.maxAimDistance();
    m_maxRocketDistance = 200.0f;
    m_minEnemyDistance = 130.0f;
    m_stateChanged = false;
}

void Fight::update(float deltaSec) {
    updateTargets();
    updateState();

    switch (m_state) {
        case 0:
            return;
        case 1:
            if (angleToTarget() > 45.0f) {
                m_ship.boardComputer()->rotateTo(m_primaryTarget->transform().position());
            } else {
                m_ship.boardComputer()->rotateTo(m_primaryTarget->transform().position());
                m_ship.boardComputer()->moveTo(m_primaryTarget->transform().position(), m_minEnemyDistance);
            }
            m_ship.boardComputer()->shootBullet(m_targets);
            break;
        case 2:
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
            m_ship.boardComputer()->shootBullet(m_targets);
            break;
        case 3:
            m_ship.boardComputer()->rotateTo(m_positionBehindTarget);
            m_ship.boardComputer()->moveTo(m_positionBehindTarget);
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
    if (m_targets.empty()) {
        return true;
    }
    return false;
}

void Fight::updateState() {
    switch (m_state) {
        case 0:
            if (m_targets.empty()) {
                return;
            } else {
                setState(1);
            }
            break;
        case 1:
            if (targetDistance() < m_maxFireDistance) {
                setState(2);
            }
            break;
        case 2:
            //printf("targetDistance: %f, minEnemyDistance: %f\n", targetDistance(), m_minEnemyDistance);
            if (targetDistance() < m_minEnemyDistance) {
                setState(3);
                m_positionBehindTarget = findPositionBehindTarget();
            }
            break;
        case 3:
            if (pointDistance(m_positionBehindTarget) < 50 && targetDistance() < m_minEnemyDistance) {
                m_positionBehindTarget = findPositionBehindTarget();
            }
            if (pointDistance(m_positionBehindTarget) > 50)
                break;
            if (targetDistance() < m_minEnemyDistance) {
                break;
            }
            if (targetDistance() < m_maxFireDistance) {
                setState(2);
            } else {
                setState(1);
            }
            break;
        default:
            printf("Unexpected case");
            return;
    }

    if (m_state > 0 && m_targets.empty()) {
        setState(0);
    }

    if (m_stateChanged) {
        m_stateChanged = false;
        updateState();
    }
}

float Fight::targetDistance() {
    return glm::length(m_ship.transform().position() - m_primaryTarget->transform().position());
}

float Fight::pointDistance(glm::vec3 point) {
    return glm::length(m_ship.transform().position() - point);
}

glm::vec3 Fight::findPositionBehindTarget() {
    float x = (rand() % 100 - 50) / 100.0f;
    float y = (rand() % 100 - 50) / 100.0f;
    glm::vec3 point = glm::vec3(x, y, -1);
    point *= 3 * m_minEnemyDistance;
    return point;
}

void Fight::setState(int newState) {
    m_stateChanged = true;
    m_state = newState;
    printf("new State: %i\n", m_state);
}

float Fight::angleToTarget() {
    glm::vec3 shipDirection = glm::vec3(0, 0, -1);
    glm::vec3 targetDirection = glm::inverse(m_ship.transform().orientation()) * glm::normalize(m_primaryTarget->transform().position() - m_ship.transform().position());
    float angle = glm::acos(glm::clamp(glm::dot(glm::normalize(shipDirection), glm::normalize(targetDirection)), 0.0f, 1.0f));
    assert(std::isfinite(angle));
    return glm::degrees(angle);
}
