#pragma once

#include <glm/gtx/quaternion.hpp>


class Math {
public:
    static glm::quat quatFromDir(const glm::vec3& dir);
};

