#pragma once

#include <type_traits>

#include <glm/glm.hpp>


template<typename T>
class SafeNormalize {
public:
    SafeNormalize(const T& v);
    SafeNormalize(const T& v, const T& fallback);

    const T& get() const;
    operator T() const;

    bool valid();


protected:
    bool m_valid;
    T m_normalized;
};

template<typename T>
SafeNormalize<T> safeNormalize(const T& v);

template<typename T>
T safeNormalize(const T& v, const T& fallback);

template<typename T>
bool normalizeable(const T& v);


#include "safenormalize.inl"
