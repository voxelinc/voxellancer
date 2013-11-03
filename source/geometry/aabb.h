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

    float left() const;
    float right() const;
    float front() const;
    float back() const;
    float top() const;
    float bottom() const;

    float axisMin(Axis axis) const;
    float axisMax(Axis axis) const;

    float width() const;
    float height() const;
    float depth() const;

    float extent(Axis axis) const;

    AABB movedLeft(float delta) const;
    AABB movedRight(float delta) const;
    AABB movedFront(float delta) const;
    AABB movedBack(float delta) const;
    AABB movedUp(float delta) const;
    AABB movedDown(float delta) const;

    AABB moved(Axis axis, float delta) const;
    AABB moved(const glm::vec3 &delta) const;

    void moveLeft(float delta);
    void moveRight(float delta);
    void moveFront(float delta);
    void moveBack(float delta);
    void moveUp(float delta);
    void moveDown(float delta);

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

