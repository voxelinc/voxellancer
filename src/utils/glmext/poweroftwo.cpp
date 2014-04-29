#include "poweroftwo.h"

#include <glm/glm.hpp>


template<>
float powerOfTwo(const glm::vec2& v) {
    return v.x * v.x + v.y * v.y;
}

template<>
float powerOfTwo(const glm::vec3& v) {
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

template<>
float powerOfTwo(const glm::vec4& v) {
    return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
}

