#include "objecthudget.h"

#include <cmath>

#include <glm/glm.hpp>

#include "utils/geometryhelper.h"
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

    calculateOpeningAngle();

    glm::vec3 direction = glm::inverse(m_hud->orientation()) * (worldObject->transform().position() - m_hud->centerOfView());
    m_orientationOffset = GeometryHelper::quatFromViewDirection(direction);
}

void ObjectHudget::draw() {
    m_voxels.draw();
}

void ObjectHudget::calculateOpeningAngle() {
    WorldObject* worldObject = m_objectDelegate->worldObject();

    float radius = worldObject->bounds().sphere().radius();
    float distance = glm::length(m_hud->centerOfView() - worldObject->transform().position());
    float alpha = std::atan2(radius, distance);

    alpha = std::max(alpha, 0.05f); // Hack, set minimum size

    m_voxels.setOpeningAngle(alpha);
}

