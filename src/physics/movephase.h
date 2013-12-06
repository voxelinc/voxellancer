#pragma once

#include <list>

#include "collision/collisiondetector.h"

#include "worldtransform.h"


class MovePhase {
static constexpr float ATOMIC_DIRECTIONAL_STEP = 0.5f;
static constexpr float ATOMIC_ANGULAR_STEP = 30.0f;
static constexpr float MAX_STEPPED_DISTANCE = 1.5f;

public:
    MovePhase(const WorldTransform& originalTransform, const WorldTransform& targetTransform);
    virtual ~MovePhase();

    const WorldTransform& originalTransform() const;
    const WorldTransform& targetTransform() const;

    bool isStepped() const;
    int stepCount() const;
    WorldTransform step(int s) const;

    float distance() const;

    void calculateSubphases(const CollisionDetector& collisionDetector);

    std::list<MovePhase*>& linearisedSubphases();


protected:
    WorldTransform m_originalTransform;
    WorldTransform m_targetTransform;

    std::list<MovePhase*> m_subphases;
    std::list<MovePhase*> m_linearisedSubphases;
    bool m_linearisedSubphasesValid;

    float m_distance;

    int m_stepCount;

    void split(const CollisionDetector& collisionDetector);
    int calculateStepCount();
};
