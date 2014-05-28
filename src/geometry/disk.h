#pragma once

#include <glm/glm.hpp>

#include "pointintersection.h"


class Ray;
class Line;

class Disk final {
public:
    Disk();
    Disk(const glm::vec3& position, const glm::vec3& normal, float radius);

    const glm::vec3& position() const;
    void setPosition(const glm::vec3& position);

    const glm::vec3& normal() const;
    void setNormal(const glm::vec3& normal);

    float radius() const;
    void setRadius(float radius);

    PointIntersection intersectionWith(const Ray& ray) const;
    PointIntersection intersectionWith(const Line& line) const;


protected:
    glm::vec3 m_position;
    glm::vec3 m_normal;
    float m_radius;
};
