#include "objectdelegatehudget.h"

#include <glm/glm.hpp>

#include "utils/math.h"
#include "hudobjectdelegate.h"

#include "hud.h"


ObjectDelegateHudget::ObjectDelegateHudget(HUD* hud, HUDObjectDelegate* objectDelegate):
    Hudget(hud),
    m_objectDelegate(objectDelegate),
    m_voxels(this)
{

}

glm::vec3 ObjectDelegateHudget::position() const {
    return m_hud->position() + orientation() * glm::vec3(0, 0, -m_hud->sphere().radius());
}

glm::quat ObjectDelegateHudget::orientation() const {
    return m_hud->orientation() * m_orientationOffset;
}

void ObjectDelegateHudget::update(float deltaSec) {
    WorldObject* worldObject = m_objectDelegate->worldObject();

    if(!worldObject) {
        return;
    }

    m_voxels.setEdgeLength(1.0f);

    glm::vec3 direction = glm::inverse(m_hud->orientation()) * (worldObject->transform().position() - m_hud->position());
    m_orientationOffset = Math::differenceFromViewDirection(direction);
}

void ObjectDelegateHudget::draw() {
    m_voxels.draw();
}

