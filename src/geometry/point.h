#pragma once

#include <glm/glm.hpp>

#include "abstractshape.h"


class Sphere;
class Transform;
template<typename T> class TAABB;

class Point: public AbstractShape {
public:
    Point();
    Point(const glm::vec3& pos);

    const glm::vec3& position() const;
    void setPosition(const glm::vec3& pos);

    virtual bool intersects(const Sphere& sphere) const override;
    virtual bool nearTo(const TAABB<int>& aabb) const override;
    virtual bool containedBy(const TAABB<int>& aabb) const override;


protected:
    glm::vec3 m_position;
};

