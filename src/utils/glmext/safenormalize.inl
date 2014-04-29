#pragma once

#include <glow/logging.h>

#include <glm/glm.hpp>


template<typename T>
SafeNormalize<T>::SafeNormalize(const T& v) {
    float sqr = glm::dot(v, v);

    m_valid = sqr > 0.0f;

    if (m_valid) {
        m_normalized = v * glm::inversesqrt(sqr);
    } else {
        glow::debug() << "SafeNormalize: Couldn't normalize " << v << ", no fallback provided";
    }
}

template<typename T>
SafeNormalize<T>::SafeNormalize(const T& v, const T& fallback) {
    float sqr = glm::dot(v, v);

    m_valid = sqr > 0.0f;
    m_normalized = m_valid ? v * glm::inversesqrt(sqr) : fallback;
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
T safeNormalize(const T& v) {
    return SafeNormalize<T>(v);
}

template<typename T>
T safeNormalize(const T& v, const T& fallback) {
    return SafeNormalize<T>(v, fallback);
}

template<typename T>
bool normalizeable(const T& v) {
    return glm::dot(v, v) > 0.0f;
}

