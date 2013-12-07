#pragma once

#include <list>
#include <glm/glm.hpp>

#include "worldtransform.h"


class WorldObject;
class CollisionDetector;

class Movement {
static constexpr float ATOMIC_DIRECTIONAL_STEP = 0.4f;
static constexpr float ATOMIC_ANGULAR_STEP = 30.0f;
static constexpr float MAX_STEPPED_DISTANCE = 1.2f;


public:
    Movement(WorldObject& worldObject, const WorldTransform& originalTransform, const WorldTransform& targetTransform);
    virtual ~Movement();

    bool perform();


protected:
    WorldObject& m_worldObject;
    CollisionDetector& m_collisionDetector;
    WorldTransform m_originalTransform;
    WorldTransform m_targetTransform;
    float m_distance;

    bool performSplitted();
    bool performStepped();
    int calculateStepCount();
    WorldTransform calculateStep(int s, int stepCount) const;
};

