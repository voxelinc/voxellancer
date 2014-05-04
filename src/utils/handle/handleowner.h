#pragma once

#include <memory>

#include "handle.h"
#include "handleimpl.h"


/**
 * Base class for Objects that should be holdable in a Handle<T>
 */
class HandleOwner {
public:
    HandleOwner();
    virtual ~HandleOwner();

    template<typename T>
    Handle<T> handle();


protected:
    void invalidate();


protected:
    std::shared_ptr<HandleImpl> m_impl;
};

template<typename T>
Handle<T> makeHandle(T* owner);

template<typename T>
Handle<T> makeHandle(T& owner);


#include "handleowner.inl"
