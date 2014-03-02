#include "gameplayscript.h"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <glow/logging.h>

#include "gamestate/gameplay/gameplay.h"

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

#include "player.h"


GamePlayScript::GamePlayScript(GamePlay* gamePlay, ScriptEngine* scriptEngine):
    Script(),
    m_gamePlay(gamePlay),
    m_scriptEngine(scriptEngine)
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
    m_lua->Register("spawn", std::function<bool(int)>([&] (int key) {
        return apiSpawn(key);
    }));
    m_lua->Register("setPosition", std::function<int(int, float, float, float)>([&] (int key, float x, float y, float z) {
        return apiSetPosition(key, x, y, z);
    }));
    m_lua->Register("setOrientation", std::function<int(int, float, float, float)>([&] (int key, float x, float y, float z) {
        return apiSetOrientation(key, x, y, z);
    }));
    m_lua->Register("position", std::function<glm::vec3(int)>([&] (int key) {
        return apiPosition(key);
    }));
    m_lua->Register("orientation", std::function<glm::vec3(int)>([&] (int key) {
        return apiOrientation(key);
    }));
     m_lua->Register("createSingleShotTimer", std::function<int(std::string, float)>([&] (std::string callback, float delta) {
       return apiCreateSingleShotTimer(callback, delta);
    }));
/*
    m_lua->Register("createLoopingTimer", std::function<int(std::string, float)>([&] (std::string callback, float delta) {
        return apiCreateLoopingTimer(callback, delta);
    }));
    m_lua->Register("onAABBEntered", std::function<int(int, float, float, float, float, float, float, std::string)>([&] (int handle, float x1, float y1, float z1, float x2, float y2, float z2, std::string callback) {
        return apiOnAABBEntered(handle, glm::vec3(x1, y1, z1), glm::vec3(x2, y2, z2), callback);
    }));
*/
}

int GamePlayScript::apiPlayerShip() {
    return m_gamePlay->player().ship()->scriptKey();
}

int GamePlayScript::apiCreateShip(const std::string& name) {
    Ship* ship = WorldObjectBuilder(name).buildShip();

    if (ship) {
        m_scriptEngine->registerScriptable(ship);
        return ship->scriptKey();
    } else {
        glow::warning("ScriptEngine: Couldn't create ship '%;'", name);
        return -1;
    }
}

bool GamePlayScript::apiSpawn(int key) {
    WorldObject* worldObject = m_scriptEngine->getWorldObject(key);

    if (worldObject) {
        World::instance()->god().scheduleSpawn(SpawnRequest(worldObject, false));
        World::instance()->god().spawn();

        return worldObject->spawnState() == SpawnState::Spawned;
    }

    return false;
}

int GamePlayScript::apiSetPosition(int key, float x, float y, float z) {
    WorldObject* worldObject = m_scriptEngine->getWorldObject(key);

    if (worldObject) {
        worldObject->transform().setPosition(glm::vec3(x, y, z));
    }
    return 0;
}


int GamePlayScript::apiSetOrientation(int key, float x, float y, float z) {
    WorldObject* worldObject = m_scriptEngine->getWorldObject(key);

    if (worldObject) {
        worldObject->transform().setOrientation(glm::quat(glm::vec3(x, y, z)));
    }
    return 0;
}

glm::vec3 GamePlayScript::apiPosition(int key) {
    WorldObject* worldObject = m_scriptEngine->getWorldObject(key);

    if (worldObject) {
        return worldObject->transform().position();
    }
    return glm::vec3(0.0f);
}

glm::vec3 GamePlayScript::apiOrientation(int key) {
    WorldObject* worldObject = m_scriptEngine->getWorldObject(key);

    if (worldObject) {
        return glm::eulerAngles(worldObject->transform().orientation());
    }
    return glm::vec3(0.0f);
}

int GamePlayScript::apiCreateSingleShotTimer(const std::string& callback, float delta) {
    m_scriptEngine->registerTimer(new SingleShotTimer(delta, [=] {
        m_lua->call(callback);
    } ));
    return 0;
}

/*
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

*/
