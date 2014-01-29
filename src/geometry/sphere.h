#pragma once

#include <glm/glm.hpp>

#include "abstractshape.h"


class Transform;
template<typename T> class TAABB;

class Sphere : public AbstractShape {
public:
    Sphere();
    Sphere(const glm::vec3 &position, float radius);
    virtual ~Sphere();

    float radius() const;
    void setRadius(float radius);

    const glm::vec3 &position() const;
    void setPosition(const glm::vec3 &position);

    bool contains(const Sphere &other) const;

    virtual bool intersects(const Sphere &other) const override;
    virtual bool nearTo(const TAABB<int>& aabb) const override;
    virtual bool containedBy(const TAABB<int>& aabb) const override;

    template<typename T> static Sphere containing(const TAABB<T>& aabb);



protected:
    glm::vec3 m_position;
    float m_radius;
};

#include "sphere.inl"
