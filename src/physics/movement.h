#pragma once

#include <list>
#include <glm/glm.hpp>

#include "worldtransform.h"


class WorldObject;
class CollisionDetector;

class Movement {


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

