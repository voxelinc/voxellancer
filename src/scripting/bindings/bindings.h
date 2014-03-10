#pragma once

#include "scripting/scriptengine.h"

class LuaWrapper;
class ScriptEngine;
class GamePlay;
class GamePlayScript;

class Bindings {
public:
    Bindings(GamePlayScript& gamePlayScript);

    virtual void initialize() = 0;

protected:
    LuaWrapper& m_lua;
    ScriptEngine& m_scriptEngine;
    GamePlay& m_gamePlay;

    template<typename Return, typename Class, typename... Args>
    void Register(const std::string & name, Return(Class::* const method) (Args...)) {
        m_lua->Register(name, static_cast<Class>(this), method);
    }

};
