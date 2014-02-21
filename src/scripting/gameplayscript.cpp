#include "gameplayscript.h"

#include <iostream>

#include "resource/worldobjectbuilder.h"

#include "scripting/elematelua/luawrapper.h"
#include "scripting/scriptengine.h"

#include "ui/objectinfo.h"

#include "utils/singleshottimer.h"
#include "utils/loopingtimer.h"

#include "world/world.h"
#include "world/god.h"

#include "worldobject/ship.h"


GamePlayScript::GamePlayScript(ScriptEngine* scriptEngine):
    Script(),
    m_scriptEngine(scriptEngine),
    m_shipHandleIncrementor(0)
{

}

void GamePlayScript::load(const std::string& path) {
    Script::load(path);

    m_lua->Register("createShip", std::function<int(std::string)>([&] (std::string name) {
        return apiCreateShip(name);
    }));
    m_lua->Register("spawnShip", std::function<int(int)>([&] (int handle) {
        return apiSpawnShip(handle);
    }));
    m_lua->Register("setPosition", std::function<int(int, float, float, float)>([&] (int handle, float x, float y, float z) {
        return apiSetPosition(handle, x, y, z);
    }));
    m_lua->Register("createSingleShotTimer", std::function<int(std::string, float)>([&] (std::string function, float delta) {
        return apiCreateSingleShotTimer(function, delta);
    }));
     m_lua->Register("createLoopingTimer", std::function<int(std::string, float)>([&] (std::string function, float delta) {
        return apiCreateLoopingTimer(function, delta);
    }));
}

int GamePlayScript::apiCreateShip(std::string name) {
    Ship *ship = WorldObjectBuilder(name).buildShip();
    ship->objectInfo().setShowOnHud(true);
    ship->objectInfo().setCanLockOn(true);

    m_shipHandles[m_shipHandleIncrementor++] = ship;

    return m_shipHandleIncrementor - 1;
}

int GamePlayScript::apiSpawnShip(int handle) {
    std::map<int, Ship*>::iterator i = m_shipHandles.find(handle);

    if (i != m_shipHandles.end()) {
        Ship* ship = i->second;
        World::instance()->god().scheduleSpawn(ship);
    } else {
        glow::info("No such ship handle '%;'", handle);
    }

    return 0;
}

int GamePlayScript::apiSetPosition(int handle, float x, float y, float z) {
    std::map<int, Ship*>::iterator i = m_shipHandles.find(handle);

    if (i != m_shipHandles.end()) {
        Ship* ship = i->second;
        ship->transform().setPosition(glm::vec3(x, y, z));
    } else {
        glow::info("No such ship handle '%;'", handle);
    }

    return 0;
}

int GamePlayScript::apiCreateSingleShotTimer(std::string function, float delta) {
    m_scriptEngine->registerTimer(new SingleShotTimer(delta, [=] {
        m_lua->call(function);
    } ));
    return 0;
}

int GamePlayScript::apiCreateLoopingTimer(std::string function, float delta) {
    m_scriptEngine->registerTimer(new LoopingTimer(delta, [=] {
        m_lua->call(function);
    } ));
    return 0;
}


