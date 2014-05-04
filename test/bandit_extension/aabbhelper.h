#pragma once

#include <bandit/assertion_frameworks/snowhouse/snowhouse/stringize.h>

namespace snowhouse {
    template<typename T>
    struct Stringizer<TAABB<T>>
    {
        static std::string ToString(const TAABB<T>& value) {
            glm::detail::tvec3<T> llf = value.llf();
            glm::detail::tvec3<T> urb = value.urb();
            return "(" + std::to_string(llf.x) + "/"+ std::to_string(llf.y) + "/"+ std::to_string(llf.z) + ")->(" +
                         std::to_string(urb.x) + "/"+ std::to_string(urb.y) + "/"+ std::to_string(urb.z) + ")";
        }
    };
}
