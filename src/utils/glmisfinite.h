#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace std {
    bool isfinite(glm::vec3 v);
    bool isfinite(glm::quat q);
}