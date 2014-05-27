#pragma once

#include <glm/glm.hpp>


class Line;
class Ray;

class Plane final {
public:
    Plane();
    Plane(const glm::vec3& position, const glm::vec3& normal);

    glm::vec3 intersectionPoint(const Ray& ray, bool& intersects) const;
    glm::vec3 intersectionPoint(const Line& line, bool& intersects) const;


protected:
    glm::vec3 m_position;
    glm::vec3 m_normal;
};

