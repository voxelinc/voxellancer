#include "geometryhelper.h"

#include "randvec.h"
#include "worldobject/worldobject.h"


float GeometryHelper::angleBetween(const glm::vec3& u, const glm::vec3& v) {
    float angle = glm::acos(glm::clamp(glm::dot(glm::normalize(u), glm::normalize(v)), -1.0f, 1.0f));
    assert(std::isfinite(angle));
    return angle;
}

float GeometryHelper::angleBetweenVectorPlane(const glm::vec3& u, const glm::vec3& v) {
    float angle = glm::asin(glm::clamp(glm::abs(glm::dot(v, u)), -1.0f, 1.0f));
    assert(std::isfinite(angle));
    return angle;
}

glm::quat GeometryHelper::quatFromTo(const glm::vec3& u, const glm::vec3& v) {
    float angle = angleBetween(u, v);
    glm::vec3 w = glm::cross(u, v);
    if (w == glm::vec3(0)) {
        w = RandVec3::randUnitVec();
    }
    return glm::angleAxis(angle, glm::normalize(w));
}

glm::quat GeometryHelper::quatFromViewDirection(const glm::vec3& direction) {
    glm::vec3 v = direction;
    glm::vec3 u = glm::vec3(0, 0, -1);

    float angle = angleBetween(u, v);
    glm::vec3 w = glm::cross(u, v);
    if (w == glm::vec3(0)) {
        w = RandVec3::randUnitVec();
    }
    return glm::angleAxis(angle, glm::normalize(w));
}

WorldObject* GeometryHelper::closestObject(WorldObject& self, std::unordered_set<WorldObject*>* objects){
    WorldObject* closestObject = nullptr;
    float closestDistance = std::numeric_limits<float>::max();

    for (WorldObject* object : *objects) {
        float distance = glm::length(object->transform().position() - self.transform().position());
        if (distance < closestDistance) {
            closestDistance = distance;
            closestObject = object;
        }
    }
    return closestObject;
}

