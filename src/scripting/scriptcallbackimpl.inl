#pragma once

#include <iostream>

#include "scripting/elematelua/luawrapper.h"
#include "scripting/script.h"


namespace {
template<typename... Args>
void callHelper(ScriptCallbackImpl<Args...>* callback, const std::string& function, Args... args) {
     std::cout << "Calling script back: " << function << " " << callback->script()->refCounter() << std::endl;
    callback->script()->lua().call(function, args...);
}
}

template<typename... Args>
ScriptCallbackImpl<Args...>::ScriptCallbackImpl(Script& script, const std::string& function, Args... args):
    m_script(makeHandle(script)),
    m_function(function),
    m_call(std::bind(callHelper<Args...>, this, function, args...))
{
}

template<typename... Args>
ScriptCallbackImpl<Args...>::~ScriptCallbackImpl() = default;

template<typename... Args>
bool ScriptCallbackImpl<Args...>::dead() const {
    return !m_script.valid();
}

template<typename... Args>
Handle<Script>& ScriptCallbackImpl<Args...>::script() {
    return m_script;
}

template<typename... Args>
void ScriptCallbackImpl<Args...>::call() {
    if (!m_script.valid()) {
        return;
    }
    m_call();
}

