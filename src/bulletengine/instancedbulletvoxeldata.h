#pragma once

#include <stdint.h>

#include <glm/glm.hpp>


class Voxel;

struct InstancedBulletVoxelData {
    InstancedBulletVoxelData(Voxel* voxel);

    glm::ivec3 cell;
    uint32_t color;
    float emissiveness;
};

