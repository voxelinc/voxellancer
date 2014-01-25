#include "geometryhelper.h"

#include "randvec.h"


float GeometryHelper::angleBetween(const glm::vec3& u, const glm::vec3& v) {
    float angle = glm::acos(glm::clamp(glm::dot(glm::normalize(u), glm::normalize(v)), 0.0f, 1.0f));
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

glm::quat GeometryHelper::quatFromViewDirection(const glm::vec3& dir) {
    glm::vec3 nd = glm::normalize(dir);

    glm::vec3 euler(
        std::asin(nd.y),
        -std::asin(nd.x),
        0.0f
        );

    return glm::quat(euler);
}