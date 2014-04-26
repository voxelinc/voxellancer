#pragma once

#include <glm/glm.hpp>


class RandVec3 {
public:
    static glm::vec3 rand(float from, float to);
    static glm::vec3 rand(const glm::vec3& from, const glm::vec3& to);
    static glm::vec3 randUnitVec();
};

