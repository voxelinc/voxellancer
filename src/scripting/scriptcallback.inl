#pragma once

#include "script.h"
#include "scriptcallbackimpl.h"


template<typename ...Args>
ScriptCallback<Args...>::ScriptCallback(Script& script, const std::string& function, Args... args) {
    m_impl.reset(new ScriptCallbackImpl<Args...>(script, function, args...));
}

template<typename ...Args>
ScriptCallback<Args...>::~ScriptCallback() = default;

