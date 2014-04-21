#pragma once

#include <memory>


class CallbackImpl;

/**
 * Abstract base class for anything that can be called back some point on the future
 * Just using a std::function<> might not be desirable when you need to make checks before
 * executing the call (think of a callback to an object that might be deleted in the meantime
 * -> Handle would need to be checked for valid()ity before calling the function on it)
 */
class Callback {
public:
    virtual ~Callback();

    void call();


protected:
    std::shared_ptr<CallbackImpl> m_impl;
};

