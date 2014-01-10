#include "camerafollowhelper.h"

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "geometry/sphere.h"



CameraFollowHelper::CameraFollowHelper(WorldObject* worldObject):
    m_worldObject(worldObject)
{

}

glm::vec3 CameraFollowHelper::position() {
//    AABB gridBoundsAABB = m_worldObject->minimalGridAABB();
//    gridBoundsAABB.setRub(boundsAABB.rub() + glm::ivec3(1, 1, 1));
//
//    AABB boundsAABB(
//        m_worldObject->transform().applyTo(gridBoundsAABB.llf()),
//        m_worldObject->transform().applyTo(gridBoundsAABB.rub())
//    );
//
//    Sphere sphere = Sphere::containing(boundsAABB);
//
//    glm::vec3 relativeOffset(0, sphere.radius() * 0.5f, -sphere.radius() * 2);
//
//    return sphere.position() + m_worldObject->transform.orientation() * relativeOffset;
    return m_worldObject->transform().position();
}

