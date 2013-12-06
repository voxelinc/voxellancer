#include "movement.h"


Movement::Movement():
    m_rootMovePhase(nullptr),
    m_movePhasesValid(false)
{
}

Movement::~Movement() {
    delete m_rootMovePhase;
}

void Movement::clear() {

}

void Movement::setOriginalTransform(const WorldTransform& originalTransform) {
    m_originalTransform = originalTransform;
    m_movePhasesValid = false;
}

void Movement::setDelta(float deltaSec, const glm::vec3& speed, const glm::vec3& angularSpeed) {
    m_targetTransform = m_originalTransform;

    m_targetTransform.moveWorld(speed * deltaSec);
    m_targetTransform.rotate(glm::quat(angularSpeed * deltaSec));

    m_movePhasesValid = false;
}

void Movement::calculatePhases(const CollisionDetector& collisionDetector) {
    delete m_rootMovePhase;
    m_rootMovePhase = new MovePhase(m_originalTransform, m_targetTransform);
    m_rootMovePhase->calculateSubphases(collisionDetector);
}

const WorldTransform& Movement::targetTransform() const {
    return m_targetTransform;
}

const std::list<MovePhase*>& Movement::movePhases() {
    if (!m_movePhasesValid) {
        m_movePhases = m_rootMovePhase->linearisedSubphases();
        m_movePhasesValid = true;
    }
    return m_movePhases;
}
