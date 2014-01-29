#pragma once

#include <functional>
#include <glm/glm.hpp>

namespace std {
    template<> struct hash<glm::ivec3>
    {
        std::size_t operator()(const glm::ivec3 &v) const {
            return (v.x ^ (v.y << 8) ^ (v.z << 16)) * 31;
        }
    };
}