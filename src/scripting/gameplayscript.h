#pragma once

#include <map>
#include <memory>

#include <glm/glm.hpp>

#include "scripting/script.h"


class Game;
class ScriptEngine;
class Ship;
class Squad;
class WorldObject;

class GamePlayScript: public Script {
public:
    GamePlayScript(Game* game, ScriptEngine* scriptEngine);

    virtual void load(const std::string& path) override;


protected:
    Game* m_game;
    ScriptEngine* m_scriptEngine;

    int m_shipHandleIncrementor;
    std::map<int, Ship*> m_shipHandles;

//    int m_squadHandleIncrementor;
//    std::map<int, std::shared_ptr<Squad>> m_squadHandles;


    int apiPlayerShip();
    int apiCreateShip(const std::string& name);
    int apiSpawn(int handle);
    int apiSetPosition(int handle, float x, float y, float z);
    int apiCreateSingleShotTimer(const std::string& callback, float delta);
    int apiCreateLoopingTimer(const std::string& callback, float delta);
    int apiOnAABBEntered(int handle, glm::vec3 llf, glm::vec3 urb, const std::string& callback);

    WorldObject* getWorldObject(int handle);
};

