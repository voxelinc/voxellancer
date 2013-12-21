#pragma once

#include <glm/glm.hpp>


class Sphere;
class WorldTransform;

class Line {
public:
    Line();
    Line(const glm::vec3& a, const glm::vec3& b);

    const glm::vec3& a() const;
    void setA(const glm::vec3& a);

    const glm::vec3& b() const;
    void setB(const glm::vec3& b);

    bool intersects(const Sphere& sphere);

    Line applied(const WorldTransform& transform) const;
    Line inverseApplied(const WorldTransform& transform) const;


protected:
    glm::vec3 m_a;
    glm::vec3 m_b;
};
