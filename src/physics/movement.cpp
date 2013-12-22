#include "movement.h"

#include <cassert>

#include "collision/collisiondetector.h"

#include "worldobject/worldobject.h"

#include "worldtree/worldtree.h"
#include "worldtree/worldtreequery.h"

#include "utils/tostring.h"




static const float ATOMIC_DIRECTIONAL_STEP = 0.4f;
static const float ATOMIC_ANGULAR_STEP = 30.0f;
static const float MAX_STEPPED_DISTANCE = 1.2f;

Movement::Movement(WorldObject& worldObject, const WorldTransform& originalTransform, const WorldTransform& targetTransform):
    m_worldObject(worldObject),
    m_collisionDetector(m_worldObject.collisionDetector()),
    m_originalTransform(originalTransform),
    m_targetTransform(targetTransform),
    m_distance(0.0f)
{
}

Movement::~Movement() {

}

bool Movement::perform() {
    assert(m_worldObject.collisionDetector().geode() != nullptr);

    AABB phaseAABB = m_collisionDetector.aabb(m_originalTransform).united(m_collisionDetector.aabb(m_targetTransform));
    WorldTreeNode* nodeHint = m_worldObject.collisionDetector().geode()->containingNode();

    if(WorldTreeQuery<AABB>(m_collisionDetector.worldTree(), phaseAABB, nodeHint, &m_worldObject).areGeodesNear()) {
        glm::vec3 directionalStep = m_targetTransform.position() - m_originalTransform.position();
        m_distance = glm::length(directionalStep);

        if(m_distance > MAX_STEPPED_DISTANCE) {
            return performSplitted();
        }
        else {
            return performStepped();
        }
    }
    else {
        m_worldObject.updateTransformAndGeode(m_targetTransform.position(), m_targetTransform.orientation());

        return true;
    }
}

bool Movement::performSplitted() {
    WorldTransform pivotTransform;

    pivotTransform.setOrientation(glm::slerp(m_originalTransform.orientation(), m_targetTransform.orientation(), 0.5f));
    pivotTransform.setPosition(glm::mix(m_originalTransform.position(), m_targetTransform.position(), 0.5f));

    Movement left(m_worldObject, m_originalTransform, pivotTransform);
    Movement right(m_worldObject, pivotTransform, m_targetTransform);

    if(left.perform()) {
        return right.perform();
    }
    else {
        return false;
    }
}

bool Movement::performStepped() {
    int stepCount = calculateStepCount();

    for (int s = 0; s < stepCount; s++) {
        WorldTransform newTransform(calculateStep(s, stepCount));
        WorldTransform oldTransform = m_worldObject.transform();

        m_worldObject.updateTransformAndGeode(newTransform.position(), newTransform.orientation());

        const std::list<VoxelCollision>& collisions = m_collisionDetector.checkCollisions();

        if(!collisions.empty()) {
            m_worldObject.updateTransformAndGeode(oldTransform.position(), oldTransform.orientation());
            return false;
        }
    }

    return true;
}

int Movement::calculateStepCount() {
    int steps = std::max(static_cast<int>(glm::ceil(m_distance / ATOMIC_DIRECTIONAL_STEP)) - 1, 1); // at least one

    float angularDiff = glm::angle(glm::inverse(m_targetTransform.orientation()) * m_originalTransform.orientation());

    if (std::isfinite(angularDiff)) { // sometimes glm::angle returns INF for really small angles
        steps = std::max(steps, static_cast<int>(glm::ceil(angularDiff / ATOMIC_ANGULAR_STEP)) - 1);
    }

    assert(steps > 0);
    return steps;
}

WorldTransform Movement::calculateStep(int s, int stepCount) const {
    WorldTransform transform;

    float rel = static_cast<float>(s + 1) / static_cast<float>(stepCount);

    transform.setOrientation(glm::slerp(m_originalTransform.orientation(), m_targetTransform.orientation(), rel));
    transform.setPosition(glm::mix(m_originalTransform.position(), m_targetTransform.position(), rel));

    return transform;
}
