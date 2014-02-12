#pragma once

class ContextDependant {
public:
    ContextDependant();
    ~ContextDependant();

protected:
    friend class WindowManager;
    virtual void beforeContextDestroy() = 0;
    virtual void afterContextRebuild() = 0;
};

