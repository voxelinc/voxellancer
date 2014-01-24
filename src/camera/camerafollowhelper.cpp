#include "camerafollowhelper.h"

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "geometry/sphere.h"


CameraFollowHelper::CameraFollowHelper():
    m_target(nullptr)
{
}

WorldObject* CameraFollowHelper::target() {
    return m_target.get()->get();
}

void CameraFollowHelper::setTarget(WorldObject* target) {
    m_target = target->handle();
}

glm::vec3 CameraFollowHelper::followPosition() {
    Sphere sphere;

    WorldObject* worldObject = m_target->get();

    sphere.setPosition(worldObject->transform().position());
    sphere.setRadius(worldObject->bounds().minimalGridAABB().diameter() * worldObject->transform().scale());

    return sphere.position() + (worldObject->transform().orientation() * glm::vec3(0.0f, 0.6f, 1.5f)) * sphere.radius();
}

