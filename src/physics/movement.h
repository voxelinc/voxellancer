#pragma once

#include <list>
#include <glm/glm.hpp>

#include "collision/collisiondetector.h"

#include "worldtransform.h"

#include "movephase.h"


class Movement {
static constexpr float MAX_STEP_DISTANCE = 5.0f;

public:
    Movement();
    virtual ~Movement();

    void clear();
    void setOriginalTransform(const WorldTransform& originalTransform);
    void setDelta(float deltaSec, const glm::vec3& speed, const glm::vec3& angularSpeed);
    void calculatePhases(const CollisionDetector& collisionDetector);

    const WorldTransform& targetTransform() const;

    const std::list<MovePhase*>& movePhases();


protected:
    WorldTransform m_originalTransform;
    WorldTransform m_targetTransform;
    MovePhase* m_rootMovePhase;
    std::list<MovePhase*> m_movePhases;
    bool m_movePhasesValid;
};

