#include "geometryhelper.h"

#include "geometry/ray.h"

#include "utils/safenormalize.h"

#include "randvec3.h"


bool GeometryHelper::intersectRectangle(const Ray* ray, const glm::vec3& p, const glm::vec3& q, const glm::vec3& r, const glm::vec3& s) {
    glm::vec3 intersectionDummy;
    return intersectRectangle(ray, p, q, r, s, intersectionDummy);
}

bool GeometryHelper::intersectRectangle(const Ray* ray, const glm::vec3& p, const glm::vec3& q, const glm::vec3& r, const glm::vec3& s, glm::vec3& intersection) {
    if (glm::intersectRayTriangle<glm::vec3>(ray->origin(), ray->direction(), p, r, s, intersection)) {
        return true;
    }
    if (glm::intersectRayTriangle<glm::vec3>(ray->origin(), ray->direction(), p, q, r, intersection)) {
        return true;
    }
    return false;

}

glm::vec3 GeometryHelper::plane(const glm::vec3& p, const glm::vec3& q, const glm::vec3& r) {
    glm::vec3 plane = glm::cross(q - p, r - p);
    assert(std::isfinite(plane.x) && std::isfinite(plane.y) && std::isfinite(plane.z));
    return plane;
}

float GeometryHelper::angleBetween(const glm::vec3& u, const glm::vec3& v) {
    if (!normalizeable(u) || !normalizeable(v)) {
        return 0.0f;
    }

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

    if (!normalizeable(w)) {
        return glm::quat();
    }

    return glm::angleAxis(angle, glm::normalize(w));
}

glm::quat GeometryHelper::quatFromViewDirection(const glm::vec3& direction) {
    glm::vec3 v = direction;
    glm::vec3 u = glm::vec3(0, 0, -1);

    float angle = angleBetween(u, v);
    glm::vec3 w = glm::cross(u, v);

    if (!normalizeable(w)) {
        return glm::quat();
    }

    return glm::angleAxis(angle, glm::normalize(w));
}
