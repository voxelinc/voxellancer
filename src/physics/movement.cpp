#include "movement.h"

#include <cassert>

#include <glm/glm.hpp>

#include <glow/logging.h>

#include "collision/collisiondetector.h"

#include "worldobject/worldobject.h"

#include "worldtree/worldtree.h"
#include "worldtree/worldtreequery.h"
#include "worldtree/worldtreegeode.h"

#include "voxel/voxelclusterbounds.h"


static const float ATOMIC_DIRECTIONAL_STEP = 0.4f;
static const float ATOMIC_ANGULAR_STEP = glm::radians(30.0f);
static const float MAX_STEPPED_DISTANCE = 1.2f;

Movement::Movement(WorldObject& worldObject, const Transform& originalTransform, const Transform& targetTransform):
    m_worldObject(worldObject),
    m_collisionDetector(m_worldObject.collisionDetector()),
    m_originalTransform(originalTransform),
    m_targetTransform(targetTransform),
    m_distance(0.0f),
    m_successful(true)
{
}

Movement::~Movement() = default;

bool Movement::perform() {
    assert(m_worldObject.collisionDetector().geode() != nullptr);

    m_successful = true;

    IAABB phaseAABB = m_worldObject.bounds().aabb(m_originalTransform).united(m_worldObject.bounds().aabb(m_targetTransform));
    WorldTreeNode* nodeHint = m_worldObject.collisionDetector().geode()->containingNode();

    if (WorldTreeQuery(m_collisionDetector.worldTree(), &phaseAABB, nodeHint, &m_worldObject.collisionFilter()).areGeodesNear()) {
        glm::vec3 directionalStep = m_targetTransform.position() - m_originalTransform.position();
        m_distance = glm::length(directionalStep);

        if (m_distance > MAX_STEPPED_DISTANCE) {
            performSplitted();
        } else {
            performStepped(phaseAABB);
        }
    } else {
        m_intersectionFreeTransform = m_targetTransform;
    }

    m_worldObject.updateTransformAndGeode(m_intersectionFreeTransform.position(), m_intersectionFreeTransform.orientation());

    return m_successful;
}

bool Movement::performSplitted() {
    Transform pivotTransform = m_originalTransform.mixed(m_targetTransform, 0.5f);

    Movement left(m_worldObject, m_originalTransform, pivotTransform);
    Movement right(m_worldObject, pivotTransform, m_targetTransform);

    m_successful = left.perform() && right.perform();
    m_intersectionFreeTransform = m_worldObject.transform();
}

bool Movement::performStepped(const IAABB& phaseAABB) {
    int stepCount = calculateStepCount();

    WorldTreeNode* nodeHint = m_worldObject.collisionDetector().geode()->containingNode();
    std::unordered_set<WorldTreeGeode*> possibleColliders = WorldTreeQuery(m_collisionDetector.worldTree(), &phaseAABB, nodeHint, &m_worldObject.collisionFilter()).nearGeodes();

    m_intersectionFreeTransform = m_worldObject.transform();

    for (int s = 0; s < stepCount; s++) {
        m_intersectionFreeTransform = m_worldObject.transform();
        Transform newTransform(calculateStep(s, stepCount));

        m_worldObject.setTransform(newTransform);

        const std::list<VoxelCollision>& collisions = m_collisionDetector.checkCollisions(possibleColliders);

        if (!collisions.empty()) {
            m_successful = false;
        } else {
            m_intersectionFreeTransform = newTransform;
        }
    }
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

Transform Movement::calculateStep(int s, int stepCount) const {
    Transform transform;

    float rel = static_cast<float>(s + 1) / static_cast<float>(stepCount);

    transform.setOrientation(glm::slerp(m_originalTransform.orientation(), m_targetTransform.orientation(), rel));
    transform.setPosition(glm::mix(m_originalTransform.position(), m_targetTransform.position(), rel));
    transform.setScale(m_originalTransform.scale());
    transform.setCenter(m_originalTransform.center());

    return transform;
}

