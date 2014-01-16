#include "camerafollowhelper.h"

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "geometry/sphere.h"



CameraFollowHelper::CameraFollowHelper(WorldObject* worldObject):
    m_worldObject(worldObject)
{

}

glm::vec3 CameraFollowHelper::followPosition() {
    Sphere sphere;

    sphere.setPosition(m_worldObject->transform().position());
    sphere.setRadius(m_worldObject->minimalGridAABB().diameter() * m_worldObject->transform().scale());

    return sphere.position() + (m_worldObject->transform().orientation() * glm::vec3(0.0f, 1.5f, 2.5f)) * sphere.radius();
}

