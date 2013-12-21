#pragma once

#include <glm/glm.hpp>


template<typename T> class TAABB;
class WorldTransform;

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

    static Sphere containing(const TAABB<float>& aabb);

    Sphere applied(const WorldTransform& transform) const;
    Sphere inverseApplied(const WorldTransform& transform) const;


protected:
    glm::vec3 m_position;
    float m_radius;
};

