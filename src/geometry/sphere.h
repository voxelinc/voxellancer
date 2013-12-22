#pragma once

#include <glm/glm.hpp>


class WorldTransform;
template<typename T> class TAABB;

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

    template<typename T> bool nearTo(const TAABB<T>& aabb) const;

    template<typename T> static Sphere containing(const TAABB<T>& aabb);

    Sphere applied(const WorldTransform& transform) const;
    Sphere inverseApplied(const WorldTransform& transform) const;


protected:
    glm::vec3 m_position;
    float m_radius;
};

#include "sphere.inl"
