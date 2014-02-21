#pragma once

#include <glm/glm.hpp>

template<typename T>
T GeometryHelper::safeNormalize(const T& value) {
    // GLM_STATIC_ASSERT(glm::detail::type<T>::is_vector, "'safeNormalize' only accept float vectors");
    // GLM_STATIC_ASSERT(glm::detail::type<T>::is_float, "'safeNormalize' only accepts float vectors");

    if (glm::length(value) == 0.0f) {
        return value;
    } else {
        return glm::normalize(value);
    }
}

