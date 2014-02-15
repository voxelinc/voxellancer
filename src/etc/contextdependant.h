#pragma once

class ContextDependant {
public:
    ContextDependant();
    ~ContextDependant();

protected:
    friend class ContextProvider;
    virtual void beforeContextDestroy() = 0;
    virtual void afterContextRebuild() = 0;
};

