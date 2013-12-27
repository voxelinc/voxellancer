#pragma once

#include <string>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <bandit/assertion_frameworks/snowhouse/snowhouse/stringize.h>
#include "utils/tostring.h"
#include "voxel/voxel.h"



namespace snowhouse {
    template<typename T>
    struct Stringizer<TAABB<T>>
    {
        static std::string ToString(const TAABB<T>& value) {
            return toString(value);
        }
    };
}
