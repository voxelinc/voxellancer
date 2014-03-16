#include "worldobjectbindings.h"

#include <memory>

#include "events/worldobjectdestroyedpoll.h"
#include "events/eventpoller.h"

#include "gamestate/gameplay/gameplay.h"

#include "player.h"

#include "resource/worldobjectbuilder.h"

#include "scripting/elematelua/luawrapper.h"

#include "world/world.h"
#include "world/god.h"
#include "world/spawnrequest.h"

#include "worldobject/ship.h"



WorldObjectBindings::WorldObjectBindings(GamePlayScript& script):
    Bindings(script)
{

}


void WorldObjectBindings::initialize()
{
    m_lua.Register("playerShip", this, &WorldObjectBindings::apiPlayerShip);
    m_lua.Register("createShip", this, &WorldObjectBindings::apiCreateShip);
    m_lua.Register("spawn", this, &WorldObjectBindings::apiSpawn);

    m_lua.Register("position", this, &WorldObjectBindings::apiPosition);
    m_lua.Register("orientation", this, &WorldObjectBindings::apiOrientation);
    m_lua.Register("setPosition", this, &WorldObjectBindings::apiSetPosition);
    m_lua.Register("setOrientation", this, &WorldObjectBindings::apiSetOrientation);
}


apikey WorldObjectBindings::apiPlayerShip() {
    if (World::instance()->player().ship()) {
        return World::instance()->player().ship()->scriptKey();
    } else {
        return 0;
    }
}

int WorldObjectBindings::apiCreateShip(const std::string& name) {
    Ship* ship = WorldObjectBuilder(name).buildShip();

    if (!ship) {
        glow::warning("WorldObjectBindings: Couldn't create ship '%;'", name);
        return -1;
    }

    m_scriptEngine.registerScriptable(ship);
    return ship->scriptKey();
}

int WorldObjectBindings::apiSpawn(apikey key) {
    WorldObject* worldObject = m_scriptEngine.get<WorldObject>(key);

    if (!worldObject) {
        return -1;
    }

    World::instance()->god().scheduleSpawn(SpawnRequest(worldObject, false));
    World::instance()->god().spawn(); // should this really happen?
    return worldObject->spawnState() == SpawnState::Spawned;
}



glm::vec3 WorldObjectBindings::apiOrientation(apikey key) {
    WorldObject* worldObject = m_scriptEngine.get<WorldObject>(key);

    if (!worldObject) {
        return glm::vec3(0.0f);
    }

    return glm::eulerAngles(worldObject->transform().orientation());
}


glm::vec3 WorldObjectBindings::apiPosition(apikey key) {
    WorldObject* worldObject = m_scriptEngine.get<WorldObject>(key);

    if (!worldObject) {
        return glm::vec3(0.0f);
    }

    return worldObject->transform().position();
}

int WorldObjectBindings::apiSetPosition(apikey key, const glm::vec3& position) {
    WorldObject* worldObject = m_scriptEngine.get<WorldObject>(key);

    if (!worldObject) {
        return -1;
    }

    worldObject->transform().setPosition(position);
    return 0;
}


int WorldObjectBindings::apiSetOrientation(apikey key, const glm::vec3& orientation) {
    WorldObject* worldObject = m_scriptEngine.get<WorldObject>(key);

    if (worldObject) {
        return -1;
    }

    worldObject->transform().setOrientation(glm::quat(orientation));
    return 0;
}

apikey WorldObjectBindings::apiOnWorldObjectDestroyed(apikey key, const std::string& callback) {
    WorldObject* worldObject = m_scriptEngine.get<WorldObject>(key);

    if (!worldObject) { return -1; }

    auto destructionPoll = std::make_shared<WorldObjectDestroyedPoll>(worldObject, [=] { m_lua.call(callback, key); });
    World::instance()->eventPoller().addPoll(destructionPoll);
    return destructionPoll->scriptKey();
}