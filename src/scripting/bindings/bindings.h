#pragma once

#include "scripting/scriptengine.h"

#include "utils/callback.h"

#include "scripting/scriptcallback.h"


class LuaWrapper;
class ScriptEngine;
class GamePlay;
class GamePlayScript;

typedef int apikey;

class Bindings {
public:
    Bindings(GamePlayScript& script);

    virtual void initialize() = 0;

    template<typename ...Args>
    std::shared_ptr<Callback> createCallback(const std::string& function, Args... args);



protected:
    GamePlayScript& m_script;
    LuaWrapper& m_lua;
    ScriptEngine& m_scriptEngine;
};


#include "bindings.inl"
