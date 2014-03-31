#pragma once

#include <glm/glm.hpp>


class RandVec3 {
public:
    static glm::vec3 rand(float from, float to);
    static glm::vec3 randUnitVec();
};

