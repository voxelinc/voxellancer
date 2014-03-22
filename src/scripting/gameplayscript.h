#pragma once

#include <list>
#include <memory>
#include <vector>

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

    /* Add a Scriptable to be hold by this script. On destruction of the script
    this Scriptable becomes invalid and will be destroyed */
    void addLocal(int key);



protected:
    ScriptEngine* m_scriptEngine;
    std::list<int> m_locals;
};

