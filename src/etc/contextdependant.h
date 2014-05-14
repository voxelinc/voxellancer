#pragma once


/**
 * A ContextDependant is a class that has resources bound to the current GL context
 * and must thus be notified before and after the context is rebuilt by the ContextProvider
 */
class ContextDependant {
public:
    ContextDependant();
    ~ContextDependant();

protected:
    friend class ContextProvider;
    virtual void beforeContextDestroy() = 0;
    virtual void afterContextRebuild() = 0;
};

