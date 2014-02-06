#include "camerafollowhelper.h"

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "geometry/sphere.h"
#include "worldobject/worldobject.h"


CameraFollowHelper::CameraFollowHelper():
    m_target(nullptr)
{
}

WorldObject* CameraFollowHelper::target() {
    return *m_target;
}

void CameraFollowHelper::setTarget(WorldObject* target) {
    m_target = target->handle();
}

glm::vec3 CameraFollowHelper::followPosition() {
    Sphere sphere;

    WorldObject* worldObject = m_target.get();

    sphere.setPosition(worldObject->transform().position());
    sphere.setRadius(worldObject->bounds().minimalGridAABB().diameter() * worldObject->transform().scale());

    if (worldObject->bounds().minimalGridAABB().diameter() > 0) {
        float sizeScaling = 1 + (5.0f / worldObject->bounds().minimalGridAABB().diameter());

        return sphere.position() + (worldObject->transform().orientation() * glm::vec3(0.0f, 0.6f * sizeScaling, 1.5f * sizeScaling)) * sphere.radius();
    } else {
        return sphere.position();
    }
}

