#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"


class GeometryHelper {
public:
    // Returns the angle between u and v
    static float angleBetween(const glm::vec3& u, const glm::vec3& v);
    // Returns the quaternion that rotates from u to v
    static glm::quat quatFromTo(const glm::vec3& u, const glm::vec3& v);
    // Returns the quaternion from (0,0,-1) to dir
    static glm::quat quatFromViewDirection(const glm::vec3& dir);

};

