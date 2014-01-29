#pragma once

#include <glm/glm.hpp>

#include "abstractshape.h"


class Sphere;
class WorldTransform;
template<typename T> class TAABB;

class Capsule : public AbstractShape {
public:
    Capsule();
    Capsule(const glm::vec3& origin, const glm::vec3& direction, const float radius);

    const glm::vec3& origin() const;
    void setOrigin(const glm::vec3& origin);

    const glm::vec3& direction() const;
    void setDirection(const glm::vec3& direction);

    const float radius() const;
    void setRadius(const float radius);

    virtual bool intersects(const Sphere& sphere) const override;
    virtual bool nearTo(const TAABB<int>& aabb) const override;
    virtual bool containedBy(const TAABB<int>& aabb) const override;


protected:
    glm::vec3 m_origin;
    glm::vec3 m_direction;
    float m_radius;
};

