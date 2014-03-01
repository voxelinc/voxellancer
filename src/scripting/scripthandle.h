#pragma once

#include "utils/handle/handle.h"


template<typename ScriptHandleType>
class ScriptHandle: public IScriptHandle {
public:
    ScriptHandle();

    virtual Scriptable* scriptable() override;


protected:
    Handle<ScriptHandleType> m_handle;
};

