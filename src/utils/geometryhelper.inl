#pragma once

#include <glm/glm.hpp>

template<typename T>
T GeometryHelper::safeNormalize(const T& value) {
	if (glm::length(value) == 0.0f) {
		return value;
	} else {
		return glm::normalize(value);
	}
}

template <typename T>
int GeometryHelper::sgn(T val) {
    return (T(0) < val) - (val < T(0));
}
