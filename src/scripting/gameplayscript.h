#pragma once

#include <map>
#include <memory>

#include <glm/glm.hpp>

#include "scripting/script.h"


class GamePlay;
class ScriptEngine;
class Ship;
class Squad;
class WorldObject;

class GamePlayScript: public Script {
public:
    GamePlayScript(GamePlay* gamePlay, ScriptEngine* scriptEngine);

    virtual void load(const std::string& path) override;


protected:
    GamePlay* m_gamePlay;
    ScriptEngine* m_scriptEngine;

    /*
        API for gameplayscripts below
    */
  /*  int apiPlayerShip();

    int apiCreateShip(const std::string& name);
    int apiSpawn(int handle);

    int apiSetPosition(int handle, float x, float y, float z);
    int apiSetOrientation(int handle, float x, float y, float z);
    glm::vec3 apiPosition(int handle);
    glm::vec3 apiOrientation(int handle);

    int apiCreateSingleShotTimer(const std::string& callback, float delta);
    int apiCreateLoopingTimer(const std::string& callback, float delta);

    int apiOnAABBEntered(int handle, glm::vec3 llf, glm::vec3 urb, const std::string& callback);

    WorldObject* getWorldObject(int handle);*/
};

