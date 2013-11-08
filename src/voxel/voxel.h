#pragma once

#include <glm/glm.hpp>

#include "geometry/sphere.h"


class Voxel
{
public:
    Voxel();
    virtual ~Voxel();

    const glm::ivec3 &gridCell();
    void setGridCell(const glm::ivec3 &cell);

protected:
    glm::ivec3 m_gridCell;
};

