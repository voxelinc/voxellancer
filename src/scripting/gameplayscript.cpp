#include "gameplayscript.h"

#include <iostream>

#include "geometry/aabb.h"

#include "resource/worldobjectbuilder.h"

#include "scripting/elematelua/luawrapper.h"
#include "scripting/polls/aabbenteredpoll.h"
#include "scripting/scriptengine.h"

#include "ui/objectinfo.h"

#include "utils/singleshottimer.h"
#include "utils/loopingtimer.h"

#include "world/world.h"
#include "world/god.h"

#include "worldobject/ship.h"

#include "game.h"
#include "player.h"


GamePlayScript::GamePlayScript(Game* game, ScriptEngine* scriptEngine):
    Script(),
    m_game(game),
    m_scriptEngine(scriptEngine),
    m_shipHandleIncrementor(0)
{

}

void GamePlayScript::load(const std::string& path) {
    Script::load(path);

    m_lua->Register("playerShip", std::function<int()>([&] () {
       return apiPlayerShip();
    }));
    m_lua->Register("createShip", std::function<int(std::string)>([&] (std::string name) {
        return apiCreateShip(name);
    }));
    m_lua->Register("spawn", std::function<int(int)>([&] (int handle) {
        return apiSpawn(handle);
    }));
    m_lua->Register("setPosition", std::function<int(int, float, float, float)>([&] (int handle, float x, float y, float z) {
        return apiSetPosition(handle, x, y, z);
    }));
    m_lua->Register("createSingleShotTimer", std::function<int(std::string, float)>([&] (std::string callback, float delta) {
        return apiCreateSingleShotTimer(callback, delta);
    }));
    m_lua->Register("createLoopingTimer", std::function<int(std::string, float)>([&] (std::string callback, float delta) {
        return apiCreateLoopingTimer(callback, delta);
    }));
    m_lua->Register("onAABBEntered", std::function<int(int, float, float, float, float, float, float, std::string)>([&] (int handle, float x1, float y1, float z1, float x2, float y2, float z2, std::string callback) {
        return apiOnAABBEntered(handle, glm::vec3(x1, y1, z1), glm::vec3(x2, y2, z2), callback);
    }));

}

int GamePlayScript::apiPlayerShip() {
    return m_scriptEngine->getWorldObjectHandle(m_game->player().ship());
}

int GamePlayScript::apiCreateShip(const std::string& name) {
    Ship *ship = WorldObjectBuilder(name).buildShip();
    ship->objectInfo().setShowOnHud(true);
    ship->objectInfo().setCanLockOn(true);

    return m_scriptEngine->registerWorldObject(ship);
}

int GamePlayScript::apiSpawn(int handle) {
    WorldObject* worldObject = m_scriptEngine->getWorldObject(handle);

    if (worldObject) {
        World::instance()->god().scheduleSpawn(worldObject);
    }
    return -1;
}

int GamePlayScript::apiSetPosition(int handle, float x, float y, float z) {
    WorldObject* worldObject = m_scriptEngine->getWorldObject(handle);

    if (worldObject) {
        worldObject->transform().setPosition(glm::vec3(x, y, z));
    }
    return 0;
}

int GamePlayScript::apiCreateSingleShotTimer(const std::string& callback, float delta) {
    m_scriptEngine->registerTimer(new SingleShotTimer(delta, [=] {
        m_lua->call(callback);
    } ));
    return 0;
}

int GamePlayScript::apiCreateLoopingTimer(const std::string& callback, float delta) {
    m_scriptEngine->registerTimer(new LoopingTimer(delta, [=] {
        m_lua->call(callback);
    } ));
    return 0;
}

int GamePlayScript::apiOnAABBEntered(int handle, glm::vec3 llf, glm::vec3 urb, const std::string& callback) {
    WorldObject* worldObject = m_scriptEngine->getWorldObject(handle);
    if (worldObject) {
        return m_scriptEngine->registerEventPoll(new AABBEnteredPoll(worldObject, AABB(llf, urb), [=] {
            m_lua->call(callback, handle);
        }));
    } else {
        return -1;
    }
}


