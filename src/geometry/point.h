#pragma once

#include <glm/glm.hpp>

#include "abstractshape.h"


class Sphere;
class WorldTransform;
template<typename T> class TAABB;

class Point: public AbstractShape {
public:
    Point();
    Point(const glm::vec3& p);

    const glm::vec3& get() const;
    void set(const glm::vec3& p);

    virtual bool intersects(const Sphere& sphere) const override;
    virtual bool nearTo(const TAABB<int>& aabb) const override;
    virtual bool containedBy(const TAABB<int>& aabb) const override;

protected:
    glm::vec3 m_p;
};

