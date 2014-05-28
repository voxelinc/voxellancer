#pragma once

#include <glm/glm.hpp>

#include "pointintersection.h"


class Line;
class Ray;

class Plane final {
public:
    Plane();
    Plane(const glm::vec3& position, const glm::vec3& normal);

    const glm::vec3& position() const;
    void setPosition(const glm::vec3& position);

    const glm::vec3& normal() const;
    void setNormal(const glm::vec3& normal);

    PointIntersection intersectionWith(const Ray& ray) const;
    PointIntersection intersectionWith(const Line& line) const;


protected:
    glm::vec3 m_position;
    glm::vec3 m_normal;
};

