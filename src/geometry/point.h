#pragma once

#include <glm/glm.hpp>

#include "abstractshape.h"


class Point: public AbstractShape {
public:
    Point();
    Point(const glm::vec3& position);

    float x() const;
    void setX(float x);

    float y() const;
    void setY(float y);

    float z() const;
    void setZ(float z);

    glm::vec3 vec3() const;

    virtual bool intersects(const Sphere& sphere) const override;
    virtual bool nearTo(const TAABB<int>& aabb) const override;
    virtual bool containedBy(const TAABB<int>& aabb) const override;


protected:
    float m_x;
    float m_y;
    float m_z;
};
