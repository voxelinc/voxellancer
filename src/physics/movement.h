#pragma once

#include <list>

#include <glm/glm.hpp>

#include "geometry/aabb.h"
#include "geometry/transform.h"


class WorldObject;
class CollisionDetector;

class Movement {
public:
    Movement(WorldObject& worldObject, const Transform& originalTransform, const Transform& targetTransform);
    virtual ~Movement();

    bool perform();


protected:
    WorldObject& m_worldObject;
    CollisionDetector& m_collisionDetector;
    Transform m_originalTransform;
    Transform m_targetTransform;
    float m_distance;


    bool performSplitted();
    bool performStepped(const IAABB& phaseAABB);
    int calculateStepCount();
    Transform calculateStep(int s, int stepCount) const;
};

