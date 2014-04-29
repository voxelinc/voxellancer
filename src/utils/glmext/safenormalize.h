#pragma once

#include <type_traits>

#include <glm/glm.hpp>


template<typename T>
class SafeNormalize {
public:
    SafeNormalize(const T& v, const T& fallback = T(0.0f));

    const T& get() const;
    operator T() const;

    bool valid();


protected:
    bool m_valid;
    T m_normalized;
};

template<typename T>
T safeNormalize(const T& v, const T& fallback = T(0.0f));

template<typename T>
bool normalizeable(const T& v);


#include "safenormalize.inl"
