#pragma once

#include <glm/glm.hpp>


struct VoxelData {
    glm::vec3 gridCell;
    uint32_t color;
    float emissiveness;
};

