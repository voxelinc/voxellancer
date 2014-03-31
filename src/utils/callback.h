#pragma once

#include <memory>


class CallbackImpl;

/**
 * Abstract base class for anything than called back
 */
class Callback {
public:
    virtual ~Callback();

    void call();


protected:
    std::shared_ptr<CallbackImpl> m_impl;
};

