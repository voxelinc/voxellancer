#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"


class GeometryHelper
{
public:
    static float angleBetween(const glm::vec3& u, const glm::vec3& v);
    static glm::quat quatFrom(const glm::vec3& u, const glm::vec3& v);

};

