#pragma once


/**
 * Backend of Callback, performs its actual operation
 */
class CallbackImpl {
public:
    virtual bool dead() const = 0;
    virtual void call() = 0;
};

