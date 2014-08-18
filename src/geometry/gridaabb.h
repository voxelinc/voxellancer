#pragma once

#include <glm/glm.hpp>

#include "axis.h"


/**
 * An AABB inside a grid, which means that an AABB from 0,0,0 to 0,0,0
 * covers exactly one cell
 */
class GridAABB {
public:
    GridAABB();
    GridAABB(const glm::ivec3 &llf, const glm::ivec3 &urb);

    const glm::ivec3 &llf() const;
    void setLLF(const glm::ivec3& llf);

    const glm::ivec3 &urb() const;
    void setURB(const glm::ivec3& urb);

    bool contains(const glm::ivec3& cell) const;

    glm::ivec3 extent() const;
    int extent(Axis axis) const;

    /**
     * Distance from LLF to URB
     */
    float diameter() const;

    bool operator==(const GridAABB& other) const;


protected:
    glm::ivec3 m_llf;
    glm::ivec3 m_urb;
};

