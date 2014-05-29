#pragma once

#include <iostream>
#include <sstream>

#include <string>
#include <glm/glm.hpp>
#include <bandit/assertion_frameworks/snowhouse/snowhouse/stringize.h>


// adds vec3 support to bandit

bool operator>=(const glm::vec3 &a, const glm::vec3 &b);

bool operator<=(const glm::vec3 &a, const glm::vec3 &b);

namespace snowhouse {
    template<>
    struct Stringizer<glm::vec3>
    {
        static std::string ToString(const glm::vec3& value) {
            return "(" + std::to_string(value.x) + "/" + std::to_string(value.y) + "/" + std::to_string(value.z) + ")";
        }
    };
}
