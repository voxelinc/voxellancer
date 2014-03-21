#pragma once

#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "scripting/script.h"


class ScriptEngine;
class Ship;
class Squad;
class WorldObject;

class GamePlayScript: public Script {
public:
    GamePlayScript(ScriptEngine* scriptEngine);
    virtual ~GamePlayScript();

    ScriptEngine& scriptEngine();
    LuaWrapper& luaWrapper();


protected:
    ScriptEngine* m_scriptEngine;
};

