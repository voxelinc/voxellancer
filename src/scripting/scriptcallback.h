#pragma once

#include <memory>
#include <string>
#include <tuple>
#include <functional>

#include "utils/callback.h"
#include "utils/handle/handle.h"


class Script;

template<typename... Args>
class ScriptCallback : public Callback {
public:
    ScriptCallback(Script& script, const std::string& function, Args... args);
    virtual ~ScriptCallback() = default;

    Handle<Script>& script();

    virtual void call() override;


protected:
    Handle<Script> m_script;
    std::string m_function;
    std::function<void()> m_call;
};


#include "scriptcallback.inl"

