#pragma once

#include <list>
#include <memory>
#include <glm/glm.hpp>

#include "physics.h"

class BulletPhysics : public Physics  {
public:
    BulletPhysics(WorldObject& worldObject);

protected:
    
    virtual void updateSpeed(float delta_sec);

};
