#pragma once

#include <list>
#include <glm/glm.hpp>

#include "axis.h"

class AABB
{
public:
    AABB();
    AABB(const glm::vec3 &llf, const glm::vec3 &rub);
    virtual ~AABB();

    const glm::vec3 &llf() const;
    void setLlf(const glm::vec3 &llf);

    const glm::vec3 &rub() const;
    void setRub(const glm::vec3 &rub);

    float axisMin(Axis axis) const;
    float axisMax(Axis axis) const;

    float extent(Axis axis) const;

    AABB moved(Axis axis, float delta) const;
    AABB moved(const glm::vec3 &delta) const;

    void move(Axis axis, float delta);
    void move(const glm::vec3 &delta);

    void expand(Axis axis, float delta);
    AABB expanded(Axis axis, float delta) const;

    bool intersects(const AABB &other) const;
    bool contains(const AABB &other) const;

    AABB united(const AABB &other) const ;
    void unite(const AABB &other);

    std::list<AABB> split(Axis axis) const;
    void split(AABB &a, AABB &b, Axis axis) const;
    std::list<AABB> recursiveSplit(int recursions, Axis axis) const;


protected:
    glm::vec3 m_llf, m_rub;
};

