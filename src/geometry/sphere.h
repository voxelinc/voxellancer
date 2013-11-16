#pragma once

#include <glm/glm.hpp>


class Sphere
{
public:
    Sphere();
    Sphere(const glm::vec3 &position, float radius);
    virtual ~Sphere();

    float radius() const;
    void setRadius(float radius);

    const glm::vec3 &position() const;
    void setPosition(const glm::vec3 &position);

    bool intersects(const Sphere &other) const;
    bool contains(const Sphere &other) const;


protected:
    glm::vec3 m_position;
    float m_radius;
};

