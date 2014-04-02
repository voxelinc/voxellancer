#pragma once

#include "handle.h"

/**
 * Base class for Objects that should be holdable in
 * a Handle<T>
 */
class HandleOwner {
public:
    template<typename T>
    Handle<T> handle();

protected:
    Handle<HandleOwner> m_handleImpl;
};
