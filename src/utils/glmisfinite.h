#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace std {
    bool isfinite(const glm::vec3& v);
    bool isfinite(const glm::quat& q);
}