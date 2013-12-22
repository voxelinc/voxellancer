#pragma once

#include <glm/glm.hpp>


class Sphere;
class WorldTransform;
template<typename T> class TAABB;

class Ray {
public:
    Ray(const glm::vec3& origin, const glm::vec3& direction);

    const glm::vec3& origin() const;
    void setOrigin(const glm::vec3& origin);

    const glm::vec3& direction() const;
    void setDirection(const glm::vec3& direction);

    bool intersects(const Sphere& sphere) const;

    template<typename T> bool nearTo(const TAABB<T>& aabb) const;

    Ray applied(const WorldTransform& transform) const;
    Ray inverseApplied(const WorldTransform& transform) const;


protected:
    glm::vec3 m_origin;
    glm::vec3 m_direction;
};

#include "ray.inl"
