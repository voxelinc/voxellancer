#include "worldobjectbindings.h"

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


int WorldObjectBindings::apiPlayerShip() {
    return m_gamePlay.player().ship()->scriptKey();
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

int WorldObjectBindings::apiSpawn(int key) {
    WorldObject* worldObject = m_scriptEngine.get<WorldObject>(key);

    if (!worldObject) {
        return -1;
    }

    World::instance()->god().scheduleSpawn(SpawnRequest(worldObject, false));
    World::instance()->god().spawn();
    return worldObject->spawnState() == SpawnState::Spawned;
}



glm::vec3 WorldObjectBindings::apiOrientation(int key) {
    WorldObject* worldObject = m_scriptEngine.get<WorldObject>(key);

    if (!worldObject) {
        return glm::vec3(0.0f);
    }

    return glm::eulerAngles(worldObject->transform().orientation());
}


glm::vec3 WorldObjectBindings::apiPosition(int key) {
    WorldObject* worldObject = m_scriptEngine.get<WorldObject>(key);

    if (!worldObject) {
        return glm::vec3(0.0f);
    }

    return worldObject->transform().position();
}

int WorldObjectBindings::apiSetPosition(int key, float x, float y, float z) {
    WorldObject* worldObject = m_scriptEngine.get<WorldObject>(key);

    if (!worldObject) {
        return -1;
    }

    worldObject->transform().setPosition(glm::vec3(x, y, z));
    return 0;
}


int WorldObjectBindings::apiSetOrientation(int key, float x, float y, float z) {
    WorldObject* worldObject = m_scriptEngine.get<WorldObject>(key);

    if (worldObject) {
        return -1;
    }

    worldObject->transform().setOrientation(glm::quat(glm::vec3(x, y, z)));
    return 0;
}
