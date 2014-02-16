#include "objecthudget.h"

#include <cmath>

#include <glm/glm.hpp>

#include "utils/geometryhelper.h"
#include "hudobjectdelegate.h"
#include "hud.h"
#include "worldobject/worldobject.h"
#include "player.h"


ObjectHudget::ObjectHudget(HUD* hud, HUDObjectDelegate* objectDelegate):
    Hudget(hud),
    m_objectDelegate(objectDelegate),
    m_objectVoxels(this),
    m_arrowVoxels(this)
{
    m_insideFov = false;
    fovx = glm::radians(42.5f);
    fovy = glm::radians(29.5f);
}

void ObjectHudget::update(float deltaSec) {
    m_insideFov = isInsideFov();
    WorldObject* worldObject = m_objectDelegate->worldObject();
    if(worldObject) {
        calculateOpeningAngle();
        pointToWorldPoint(worldObject->transform().position());
    }
    if (!m_insideFov) {
        m_arrowVoxels.updateDirection(closestPointInsideFov());
    }
}

void ObjectHudget::draw() {
    m_objectVoxels.draw();
    if (!m_insideFov) {
        m_arrowVoxels.draw();
    }
}

void ObjectHudget::calculateOpeningAngle() {
    WorldObject* worldObject = m_objectDelegate->worldObject();

    float radius = worldObject->bounds().sphere().radius();
    float distance = glm::length(m_hud->centerOfView() - worldObject->transform().position());
    float alpha = std::atan2(radius, distance) * 0.95f;

    alpha = std::max(alpha, 0.04f); // Hack, set minimum size

    m_objectVoxels.setOpeningAngle(alpha);
}

HUDObjectDelegate* ObjectHudget::objectDelegate() {
    return m_objectDelegate;
}

bool ObjectHudget::isAt(const Ray& ray) const {
    if (!m_insideFov) {
        return m_arrowVoxels.isAt(ray) || m_objectVoxels.isAt(ray);
    }
    return m_objectVoxels.isAt(ray);
}


void ObjectHudget::setTargeted(bool targeted) {
    m_arrowVoxels.setTarget(targeted);
    m_targeted = targeted;
}

bool ObjectHudget::isTargeted() {
    return m_targeted;
}

bool ObjectHudget::isInsideFov() {
    if (GeometryHelper::angleBetweenVectorPlane(localDirection(), glm::vec3(0, 1, 0)) < fovy &&
        GeometryHelper::angleBetweenVectorPlane(localDirection(), glm::vec3(1, 0, 0)) < fovx) {
        return true;
    } 
    return false;
}

glm::vec3 ObjectHudget::closestPointInsideFov() {
    glm::vec3 planeNormalX(glm::cos(fovx), 0, glm::cos(glm::radians(90.0f) - fovx));
    glm::vec3 planeNormalY(0, glm::cos(fovy), glm::cos(glm::radians(90.0f) - fovy));
    glm::vec3 planeDirection(glm::abs(localDirection().y), -glm::abs(localDirection().x), 0);

    glm::vec3 intersectionX = glm::cross(planeNormalX, planeDirection);
    glm::vec3 intersectionY = glm::cross(planeNormalY, planeDirection);
    float angleX = GeometryHelper::angleBetween(intersectionX, glm::vec3(0, 0, -1));
    float angleY = GeometryHelper::angleBetween(intersectionY, glm::vec3(0, 0, -1));

    glm::vec3 pointInsideFov;

    if (angleX < angleY) {
        pointInsideFov = glm::normalize(intersectionX);
    } else {
        pointInsideFov = glm::normalize(intersectionY);
    }
    pointInsideFov.x = glm::abs(pointInsideFov.x);
    pointInsideFov.y = glm::abs(pointInsideFov.y);
    pointInsideFov.z = glm::abs(pointInsideFov.z)*-1;
    if (localDirection().x < 0) {
        pointInsideFov.x *= -1;
    }
    if (localDirection().y < 0) {
        pointInsideFov.y *= -1;
    }
    return pointInsideFov;
}

void ObjectHudget::onClick(int button) {
    m_hud->player()->setTarget(m_objectDelegate->worldObject());
}