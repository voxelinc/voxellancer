#pragma once

#include <stdint.h>

#include <glm/gtx/quaternion.hpp>


class Math {
public:
    /*
    Returns the quaternion that is to be added to the local-coordinate-system view direction (0,0,-1)
    to look into the local-coordinate-system view direction dir
    */
    static glm::quat quatFromViewDirection(const glm::vec3& dir);

    static uint32_t nextPowerOf2(uint32_t n);

};

