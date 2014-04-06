#pragma once

#include <string>

#include "utils/callback.h"
#include "utils/handle/handle.h"


class Script;

template<typename... Args>
class ScriptCallback : public Callback {
public:
    ScriptCallback(Script& script, const std::string& function, Args... args);
    virtual ~ScriptCallback();
};


#include "scriptcallback.inl"

