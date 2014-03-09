#include "gameplayscript.h"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <glow/logging.h>

#include "ai/aitask.h"
#include "ai/character.h"
#include "ai/basictasks/flytotask.h"

#include "events/eventpoller.h"
#include "events/singleshottimer.h"
#include "events/loopingtimer.h"
#include "events/aabbenteredpoll.h"

#include "gamestate/gameplay/gameplay.h"

#include "geometry/aabb.h"

#include "resource/worldobjectbuilder.h"

#include "scripting/elematelua/luawrapper.h"
#include "scripting/scriptengine.h"

#include "ui/objectinfo.h"

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

    m_lua->RegisterMethod("playerShip", this, &GamePlayScript::apiPlayerShip);

    m_lua->RegisterMethod("createShip", this, &GamePlayScript::apiCreateShip);

    m_lua->RegisterMethod("spawn", this, &GamePlayScript::apiSpawn);
    
    m_lua->RegisterMethod("setPosition", this, &GamePlayScript::apiSetPosition);
    
    m_lua->RegisterMethod("setOrientation", this, &GamePlayScript::apiSetOrientation);
    
    m_lua->RegisterMethod("position", this, &GamePlayScript::apiPosition);
    
    m_lua->RegisterMethod("orientation", this, &GamePlayScript::apiOrientation);
    
    m_lua->RegisterMethod("setActive", this, &GamePlayScript::apiSetEventActive);
    
    m_lua->RegisterMethod("createSingleShotTimer", this, &GamePlayScript::apiCreateSingleShotTimer);
    
    m_lua->RegisterMethod("createLoopingTimer", this, &GamePlayScript::apiCreateLoopingTimer);
    
    m_lua->RegisterMethod("onAABBEntered", this, &GamePlayScript::apiOnAABBEntered);
    
    m_lua->RegisterMethod("createFlyToTask", this, &GamePlayScript::apiCreateFlyToTask);
    
    m_lua->RegisterMethod("setTargetPoint", this, &GamePlayScript::apiSetTargetPoint);
    
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
        glow::warning("GamePlayScript: Couldn't create ship '%;'", name);
        return -1;
    }
}

bool GamePlayScript::apiSpawn(int key) {
    WorldObject* worldObject = m_scriptEngine->get<WorldObject>(key);

    if (worldObject) {
        World::instance()->god().scheduleSpawn(SpawnRequest(worldObject, false));
        World::instance()->god().spawn();

        return worldObject->spawnState() == SpawnState::Spawned;
    }

    return false;
}

int GamePlayScript::apiSetPosition(int key, float x, float y, float z) {
    WorldObject* worldObject = m_scriptEngine->get<WorldObject>(key);

    if (worldObject) {
        worldObject->transform().setPosition(glm::vec3(x, y, z));
    }
    return 0;
}


int GamePlayScript::apiSetOrientation(int key, float x, float y, float z) {
    WorldObject* worldObject = m_scriptEngine->get<WorldObject>(key);

    if (worldObject) {
        worldObject->transform().setOrientation(glm::quat(glm::vec3(x, y, z)));
    }
    return 0;
}

glm::vec3 GamePlayScript::apiPosition(int key) {
    WorldObject* worldObject = m_scriptEngine->get<WorldObject>(key);

    if (worldObject) {
        return worldObject->transform().position();
    }
    return glm::vec3(0.0f);
}

glm::vec3 GamePlayScript::apiOrientation(int key) {
    WorldObject* worldObject = m_scriptEngine->get<WorldObject>(key);

    if (worldObject) {
        return glm::eulerAngles(worldObject->transform().orientation());
    }
    return glm::vec3(0.0f);
}

int GamePlayScript::apiSetEventActive(int key, bool active) {
    EventPoll* poll = m_scriptEngine->get<EventPoll>(key);

    if (poll) {
        poll->setActive(active);
    }

    return 0;
}

int GamePlayScript::apiCreateSingleShotTimer(const std::string& callback, float delta) {
    auto timer = std::make_shared<SingleShotTimer>(delta, [=] { m_lua->call(callback); } );
    World::instance()->eventPoller().addPoll(timer);
    return timer->scriptKey();
}

int GamePlayScript::apiCreateLoopingTimer(const std::string& callback, float delta) {
    auto timer = std::make_shared<LoopingTimer>(delta, [=] { m_lua->call(callback); } );
    World::instance()->eventPoller().addPoll(timer);
    return timer->scriptKey();
}

int GamePlayScript::apiOnAABBEntered(int key, glm::vec3 llf, glm::vec3 urb, const std::string& callback) {
    WorldObject* worldObject = m_scriptEngine->get<WorldObject>(key);
    if(!worldObject) {
        return -1;
    }

    auto enteredPoll = std::make_shared<AABBEnteredPoll>(worldObject, AABB(llf, urb), [=] { m_lua->call(callback, key); });
    World::instance()->eventPoller().addPoll(enteredPoll);
    return enteredPoll->scriptKey();
}

int GamePlayScript::apiCreateFlyToTask(int key) {
    Ship* ship = m_scriptEngine->get<Ship>(key);
    if (!ship) {
        return -1;
    }

    FlyToTask* flyToTask = new FlyToTask(ship->boardComputer());

    m_scriptEngine->registerScriptable(flyToTask);

    Character* character = ship->character();
    if (!character) {
        glow::warning("GamePlayScript: Ship '%;' has no Character", key);
        return -1;
    }
    character->setTask(std::shared_ptr<AiTask>(flyToTask));

    return flyToTask->scriptKey();
}

int GamePlayScript::apiSetTargetPoint(int key, float x, float y, float z) {
    FlyToTask* flyToTask = m_scriptEngine->get<FlyToTask>(key);
    if (!flyToTask) {
        return -1;
    }

    flyToTask->setTargetPoint(glm::vec3(x, y, z));
    return 0;
}

