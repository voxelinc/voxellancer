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
    const glm::vec3 &rub() const;

    float left() const;
    float right() const;
    float front() const;
    float back() const;
    float top() const;
    float bottom() const;

    AABB movedLeft(float delta) const;
    AABB movedRight(float delta) const;
    AABB movedFront(float delta) const;
    AABB movedBack(float delta) const;
    AABB movedUp(float delta) const;
    AABB movedDown(float delta) const;

    AABB moved(const glm::vec3 &delta) const;

    void moveLeft(float delta);
    void moveRight(float delta);
    void moveFront(float delta);
    void moveBack(float delta);
    void moveUp(float delta);
    void moveDown(float delta);

    void move(const glm::vec3 &delta);

    bool intersects(const AABB &other) const;
    bool contains(const AABB &other) const;

    std::list<AABB> split(Axis axis);
    std::list<AABB> recursiveSplit(int depth, Axis axis);


protected:
    glm::vec3 m_llf, m_rub;

};

