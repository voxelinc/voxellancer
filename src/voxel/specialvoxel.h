#pragma once

#include "voxel/voxel.h"


class SpecialVoxel: public Voxel {
public:
    SpecialVoxel(const glm::ivec3& gridCell, int index, uint32_t color, float mass, float hp);

    int index() const;


protected:
    int m_index;
};

