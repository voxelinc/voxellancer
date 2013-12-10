#pragma once

#include <glm/glm.hpp>

#include "physics.h"

class BulletPhysics : public Physics  {
public:
    BulletPhysics(WorldObject& worldObject);

protected:
    
    virtual void updateSpeed(float delta_sec);

};
