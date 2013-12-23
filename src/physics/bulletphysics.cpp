#include "bulletphysics.h"

#include <glm/gtx/quaternion.hpp>


BulletPhysics::BulletPhysics(WorldObject& worldObject, float scale) :
    Physics(worldObject, scale)
{
}

void BulletPhysics::updateSpeed(float deltaSec){
    //We don't handle these, they are by definition 0 for bullets
    assert(m_acceleration == glm::vec3(0));
    assert(m_angularAcceleration == glm::vec3(0));
}
