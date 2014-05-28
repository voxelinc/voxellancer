#pragma once

#include <glm/glm.hpp>

#include "intersection.h"


class PointIntersection : public Intersection {
public:
    PointIntersection();
    PointIntersection(const glm::vec3& point);
    virtual ~PointIntersection();

    const glm::vec3& point();
    void setPoint(const glm::vec3& point);

    operator const glm::vec3&() const;


protected:
    glm::vec3 m_point;
};

