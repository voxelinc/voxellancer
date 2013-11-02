#pragma once

#include "glm/glm.hpp"

class Sphere
{
public:
    Sphere();
    virtual ~Sphere();

    const glm::vec3 &center() const;
    void setCenter(glm::vec3 &center);

    float radius() const;
    void setRadius(float radius);

protected:
    glm::vec3 m_center;
    float m_radius;
};
