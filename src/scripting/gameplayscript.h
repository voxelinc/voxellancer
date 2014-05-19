#pragma once

#include <list>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "scripting/script.h"

class EventPoll;
class Scriptable;
class ScriptEngine;
class Ship;
class Squad;
class WorldObject;

class GamePlayScript: public Script {
public:
    GamePlayScript(ScriptEngine& scriptEngine);
    virtual ~GamePlayScript();

    ScriptEngine& scriptEngine();
    LuaWrapper& luaWrapper();


protected:
    ScriptEngine* m_scriptEngine;

    void addGamePlayBindings();
};

