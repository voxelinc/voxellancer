#pragma once

#include <vector>

#include "aabb.h"

class Grid3dAABB : public IAABB
{
public:
    Grid3dAABB();
    Grid3dAABB(const IAABB &iaabb);
    Grid3dAABB(const glm::ivec3 &llf, const glm::ivec3 &rub);

    virtual int extent(Axis axis) const;

    std::list<Grid3dAABB> split(Axis axis) const;
    void split(Grid3dAABB &a, Grid3dAABB &b, Axis axis) const;
    std::list<Grid3dAABB> recursiveSplit(int recursions, Axis axis) const;

    bool operator==(const Grid3dAABB &other) const;
};

