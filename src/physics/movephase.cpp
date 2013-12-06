#include "movephase.h"

#include <set>
#include <cassert>
#include <iostream>

#include "worldtree/worldtree.h"


MovePhase::MovePhase(const WorldTransform& originalTransform, const WorldTransform& targetTransform):
    m_originalTransform(originalTransform),
    m_targetTransform(targetTransform),
    m_linearisedSubphasesValid(false),
    m_distance(0.0f),
    m_stepCount(0)
{

}

MovePhase::~MovePhase() {
    for(MovePhase* subphase : m_subphases) {
        delete subphase;
    }
}

const WorldTransform& MovePhase::originalTransform() const {
    return m_originalTransform;
}

const WorldTransform& MovePhase::targetTransform() const {
    return m_targetTransform;
}

bool MovePhase::isStepped() const {
    return m_stepCount > 0;
}

int MovePhase::stepCount() const {
    return m_stepCount;
}

WorldTransform MovePhase::step(int s) const {
    WorldTransform transform;

    float rel = static_cast<float>(s + 1) / m_stepCount;

    transform.setOrientation(glm::slerp(m_originalTransform.orientation(), m_targetTransform.orientation(), rel));
    transform.setPosition(glm::mix(m_originalTransform.position(), m_targetTransform.position(), rel));

    return transform;
}

float MovePhase::distance() const {
    return m_distance;
}

void MovePhase::calculateSubphases(const CollisionDetector& collisionDetector) {
    AABB phaseAABB = collisionDetector.aabb(m_originalTransform).united(collisionDetector.aabb(m_targetTransform));

    std::set<WorldTreeGeode*> possibleCollisions = collisionDetector.worldTree()->geodesInAABB(phaseAABB);

    if(!possibleCollisions.empty()) {
        glm::vec3 directionalStep = m_targetTransform.position() - m_originalTransform.position();
        m_distance = glm::length(directionalStep);

        if(m_distance > MAX_STEPPED_DISTANCE) {
            split(collisionDetector);
        }
        else {
            m_stepCount = calculateStepCount();
        }
    }
    else {
        glm::vec3 directionalStep = m_targetTransform.position() - m_originalTransform.position();
        m_distance = glm::length(directionalStep);
    }
}

std::list<MovePhase*>& MovePhase::linearisedSubphases() {
    if (!m_linearisedSubphasesValid) {
        m_linearisedSubphases.clear();
        if(m_subphases.size() > 0) {
            for(MovePhase* subphase : m_subphases) {
                m_linearisedSubphases.splice(m_linearisedSubphases.end(), subphase->linearisedSubphases());
            }
        }
        else {
            MovePhase *thisClone = new MovePhase(m_originalTransform, m_targetTransform);
            thisClone->m_stepCount = m_stepCount;
            thisClone->m_distance = m_distance;
            m_linearisedSubphases.push_back(thisClone);
        }
        m_linearisedSubphasesValid = true;
    }

    return m_linearisedSubphases;
}

void MovePhase::split(const CollisionDetector& collisionDetector) {
    WorldTransform pivotTransform;

    pivotTransform.setOrientation(glm::slerp(m_originalTransform.orientation(), m_targetTransform.orientation(), 0.5f));
    pivotTransform.setPosition(glm::mix(m_originalTransform.position(), m_targetTransform.position(), 0.5f));

    MovePhase* a = new MovePhase(m_originalTransform, pivotTransform);
    MovePhase* b = new MovePhase(pivotTransform, m_targetTransform);

    a->calculateSubphases(collisionDetector);
    b->calculateSubphases(collisionDetector);

    m_subphases.push_back(a);
    m_subphases.push_back(b);
}

int MovePhase::calculateStepCount() {
    int steps = std::max(static_cast<int>(glm::ceil(m_distance / ATOMIC_DIRECTIONAL_STEP)) - 1, 1); // at least one!
    float angularDiff = glm::angle(glm::inverse(m_targetTransform.orientation()) * m_originalTransform.orientation());

    if (!std::isfinite(angularDiff)) { // sometimes glm::angle returns INF for really small angles
        steps = std::max(steps, static_cast<int>(glm::ceil(angularDiff / ATOMIC_ANGULAR_STEP)) - 1);
    }

    assert(steps > 0);
    return steps;
}

//        m_worldObject.collisionDetector().updateGeode();
//        const std::list<Collision> & collisions = m_worldObject.collisionDetector().checkCollisions();
//        if (!collisions.empty()) {
//            assert(i > 0); // you're stuck, hopefully doesn't happen!
//            m_worldObject.transform().setOrientation(glm::slerp(m_oldTransform.orientation(), m_newTransform.orientation(), (i - 1) / steps));
//            m_worldObject.transform().setPosition(glm::mix(m_oldTransform.position(), m_newTransform.position(), (i - 1) / steps));
//            assert(std::isfinite(m_worldObject.transform().orientation().x));
//            break;
//        }
