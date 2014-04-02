#pragma once

#include <memory>


class WorldObject;
class Ship;
template<typename T> class HandleImpl;


/**
 *   A Handle to an object is a secure way to reference an object that might get deleted at another place
 *
 *   Preferably, the referenced object itself should provide a handle to itself that other objects can
 *   obtain. Once the referenced object is deleted, all referencing handles turn to invalid.
 */
template<typename T>
class Handle {
public:
    explicit Handle(T* object);
    Handle(const Handle<T>& other);
    Handle(const Handle<T>&& rother);
    ~Handle();

    T* get();
    const T* get() const;

    T* operator->();
    const T* operator->() const;

    T* operator*();
    const T* operator*() const;

    Handle<T>& operator=(const Handle<T>& other);
    Handle<T>& operator=(const Handle<T>&& rother);

    /**
     * The root-Handle is the handle created directly from the pointer to the referenced object
     * Copies from a root handle aren't root.
     */
    bool root() const;

    bool valid() const;
    void invalidate();


protected:
    std::shared_ptr<HandleImpl<T>> m_impl;
    bool m_root;
};

#include "handle.inl"
