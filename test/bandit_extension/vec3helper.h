#pragma once

#include <string>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <bandit/assertion_frameworks/snowhouse/snowhouse/stringize.h>
#include "utils/tostring.h"


// adds vec3 support to bandit

bool operator>=(const glm::vec3 &a, const glm::vec3 &b);

bool operator<=(const glm::vec3 &a, const glm::vec3 &b);

namespace snowhouse {
    template<>
    struct Stringizer<glm::vec3>
    {
        static std::string ToString(const glm::vec3& value) {
            return toString(value);
        }
    };
}
