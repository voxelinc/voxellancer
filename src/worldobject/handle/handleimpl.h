#pragma once

#include <memory>

template<class T>
class HandleImpl {

public:
    explicit HandleImpl(T* object);

    T* get();
    const T* get() const;

    bool valid() const;

    void invalidate();

protected:
    T* m_object;
};

#include "handleimpl.inl"