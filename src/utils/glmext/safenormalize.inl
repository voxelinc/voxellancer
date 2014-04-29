#pragma once

#include <glow/logging.h>

#include <glm/glm.hpp>

#include "poweroftwo.h"


template<typename T>
SafeNormalize<T>::SafeNormalize(const T& v, const T& fallback) {
    float sqr = powerOfTwo(v);

    m_valid = sqr > 0.0f;

    if (m_valid) {
        m_normalized = v * glm::inversesqrt(sqr);
    } else {
  //      glow::debug() << "SafeNormalize: " << v << " cannot be normalized";
        m_normalized = fallback;
    }
}

template<typename T>
const T& SafeNormalize<T>::get() const {
    return m_normalized;
}

template<typename T>
SafeNormalize<T>::operator T() const {
    return m_normalized;
}

template<typename T>
bool SafeNormalize<T>::valid() {
    return m_valid;
}

template<typename T>
T safeNormalize(const T& v, const T& fallback) {
    return SafeNormalize<T>(v, fallback);
}

template<typename T>
bool normalizeable(const T& v) {
    return powerOfTwo(v) > 0.0f;
}

