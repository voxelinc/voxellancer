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

    /*
        API for gameplayscripts below
    */
    bool apiValid(int key);
    int apiShowText(const std::string& string);
    int apiShowTextFor(const std::string& string, int seconds);

    int apiSetEventActive(int key, bool active);

    int apiCreateSingleShotTimer(const std::string& callback, float delta);
    int apiCreateLoopingTimer(const std::string& callback, float delta);

    int apiOnAABBEntered(int key, glm::vec3 llf, glm::vec3 urb, const std::string& callback);

};

