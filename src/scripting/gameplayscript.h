#pragma once

#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "scripting/script.h"


class GamePlay;
class ScriptEngine;
class Ship;
class Squad;
class WorldObject;
class Bindings;

class GamePlayScript: public Script {
public:
    GamePlayScript(GamePlay* gamePlay, ScriptEngine* scriptEngine);
    virtual ~GamePlayScript();

    void initializeBindings();

    ScriptEngine& scriptEngine();
    GamePlay& gamePlay();
    LuaWrapper& luaWrapper();

protected:
    GamePlay* m_gamePlay;
    ScriptEngine* m_scriptEngine;

    std::vector<std::unique_ptr<Bindings>> m_bindings;

};

