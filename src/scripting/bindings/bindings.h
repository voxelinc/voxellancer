#pragma once

#include "scripting/scriptengine.h"

class LuaWrapper;
class ScriptEngine;
class GamePlay;
class GamePlayScript;

typedef int apikey;

class Bindings {
public:
    Bindings(GamePlayScript& gamePlayScript);

    virtual void initialize() = 0;

protected:
    LuaWrapper& m_lua;
    ScriptEngine& m_scriptEngine;

};
