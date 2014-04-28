#pragma once


template<typename T>
class SafeNormalize {
public:
    SafeNormalize(const T& vec);

    bool valid() const;

    const T& get();


protected:
    bool m_valid;
    T m_vec;
};


#include "safenormalize.inl"
