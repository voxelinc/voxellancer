#pragma once

#include <functional>
#include <string>

#include "utils/callbackimpl.h"


class Script;

template<typename... Args>
class ScriptCallbackImpl : public CallbackImpl {
public:
    ScriptCallbackImpl(Script& script, const std::string& function, Args... args);
    virtual ~ScriptCallbackImpl();

    virtual void call() override;

    Handle<Script>& script();


protected:
    Handle<Script> m_script;
    std::string m_function;
    std::function<void()> m_call;
};


#include "scriptcallbackimpl.inl"
