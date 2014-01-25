#include "objecthudget.h"

#include <glm/glm.hpp>

#include "utils/math.h"
#include "hudobjectdelegate.h"

#include "hud.h"


ObjectHudget::ObjectHudget(HUD* hud, HUDObjectDelegate* objectDelegate):
    Hudget(hud),
    m_objectDelegate(objectDelegate),
    m_voxels(this)
{

}

glm::vec3 ObjectHudget::position() const {
    return m_hud->position() + orientation() * glm::vec3(0, 0, -m_hud->sphere().radius());
}

glm::quat ObjectHudget::orientation() const {
    return m_hud->orientation() * m_orientationOffset;
}

void ObjectHudget::update(float deltaSec) {
    WorldObject* worldObject = m_objectDelegate->worldObject();

    if(!worldObject) {
        return;
    }

    m_voxels.setEdgeLength(1.0f);

    glm::vec3 direction = glm::inverse(m_hud->orientation()) * (worldObject->transform().position() - m_hud->position());
    m_orientationOffset = Math::differenceFromViewDirection(direction);
}

void ObjectHudget::draw() {
    m_voxels.draw();
}

