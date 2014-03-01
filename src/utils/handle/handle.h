#pragma once

#include <memory>


class WorldObject;
class Ship;

template<class T>
class HandleImpl;

template<class T>
class Handle {
public:
    explicit Handle(T* object);

    T* get();
    const T* get() const;

    T* operator->();
    const T* operator->() const;

    T* operator*();
    const T* operator*() const;

    bool valid() const;

    void invalidate();


protected:
    std::shared_ptr<HandleImpl<T>> m_impl;
};

#include "handle.inl"
