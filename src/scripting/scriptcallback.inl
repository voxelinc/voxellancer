#pragma once

#include "scripting/elematelua/luawrapper.h"
#include "scripting/script.h"


namespace {
template<typename ...Args>
void call(ScriptCallback<Args...>* callback, const std::string& function, Args... args) {
    callback->script()->lua().call(function, args...);
}
}

template<typename ...Args>
ScriptCallback<Args...>::ScriptCallback(Script& script, const std::string& function, Args... args):
    m_script(script.handle()),
    m_function(function),
    m_call(std::bind(::call<Args...>, this, function, args...))
{

}

template<typename ...Args>
Handle<Script>& ScriptCallback<Args...>::script() {
    return m_script;
}

template<typename ...Args>
void ScriptCallback<Args...>::call() {
    if (!m_script.valid()) {
        return;
    }
    m_call();
}

