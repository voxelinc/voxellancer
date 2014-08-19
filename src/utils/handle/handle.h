#pragma once

#include <memory>


class WorldObject;
class Ship;
class HandleImpl;


/**
 * A Handle to an object is a secure way to reference an object that might get deleted at another place
 * In that case valid() will return false and the getters (get(), operator->(), operator*()) will return nullptr
 * Obtainable from a HandleOwner
 */
template<typename T>
class Handle final {
public:
    Handle();
    explicit Handle(const std::shared_ptr<HandleImpl>& impl);

    T* get();
    const T* get() const;

    bool valid() const;

    operator bool() const;

    T* operator->();
    const T* operator->() const;

    T* operator*();
    const T* operator*() const;

    Handle& operator=(T& other);

    bool operator==(const T* other) const;
    bool operator==(const T& other) const;


protected:
    std::shared_ptr<HandleImpl> m_impl;
    T* m_referenced;
};


#include "handle.inl"
