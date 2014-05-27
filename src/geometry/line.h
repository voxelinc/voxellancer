#pragma once

#include <glm/glm.hpp>

#include "abstractshape.h"


class Sphere;
class Transform;
template<typename T> class TAABB;

class Line: public AbstractShape {
public:
    Line();
    Line(const glm::vec3& a, const glm::vec3& b);

    const glm::vec3& a() const;
    void setA(const glm::vec3& a);

    const glm::vec3& b() const;
    void setB(const glm::vec3& b);

    float length() const;

    virtual bool intersects(const Sphere& sphere) const override;
    virtual bool nearTo(const TAABB<int>& aabb) const override;
    virtual bool containedBy(const TAABB<int>& aabb) const override;


protected:
    glm::vec3 m_a;
    glm::vec3 m_b;
};

