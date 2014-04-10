#pragma once


/**
 * Backend of Callback, performs its actual operation
 */
class CallbackImpl {
public:
    virtual void call() = 0;
};

