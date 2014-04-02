#include "camerafollowhelper.h"

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "geometry/sphere.h"
#include "worldobject/worldobject.h"
#include "voxel/voxelclusterbounds.h"


CameraFollowHelper::CameraFollowHelper():
    m_cameraOffset("general.cameraOffset")
{
}

WorldObject* CameraFollowHelper::target() {
    return *m_target;
}

void CameraFollowHelper::setTarget(WorldObject* target) {
    m_target = target->handle<WorldObject>();
}

glm::vec3 CameraFollowHelper::followPosition() {
    Sphere sphere;

    WorldObject* worldObject = m_target.get();

    sphere.setPosition(worldObject->transform().position());
    sphere.setRadius(worldObject->bounds().minimalGridAABB().diameter() * worldObject->transform().scale());

    if (worldObject->bounds().sphere().radius() > 0) {
        float sizeScaling = 1 + (5.0f / worldObject->bounds().sphere().radius());
        return sphere.position() + (worldObject->transform().orientation() * m_cameraOffset.get() * sizeScaling) * sphere.radius();
    } else {
        return sphere.position();
    }
}

