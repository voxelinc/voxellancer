#include "worldobjectbindings.h"

#include <memory>

#include "events/worldobjectdestroyedpoll.h"
#include "events/aabbenteredpoll.h"

#include "gamestate/gameplay/gameplay.h"

#include "geometry/aabb.h"

#include "worldobject/worldobjectinfo.h"

#include "player.h"

#include "resource/worldobjectbuilder.h"

#include "scripting/gameplayscript.h"
#include "scripting/elematelua/luawrapper.h"
#include "scripting/gameplayscript.h"
#include "scripting/scriptcallback.h"
#include "scripting/scriptengine.h"

#include "universe/sector.h"
#include "universe/universe.h"

#include "worldobject/ship.h"



WorldObjectBindings::WorldObjectBindings(GamePlayScript& script):
    Bindings(script)
{

}

void WorldObjectBindings::bind() {
    m_lua.Register("playerShip", this, &WorldObjectBindings::apiPlayerShip);
    m_lua.Register("createShip", this, &WorldObjectBindings::apiCreateShip);
    m_lua.Register("createWorldObject", this, &WorldObjectBindings::apiCreateWorldObject);
    m_lua.Register("spawn", this, &WorldObjectBindings::apiSpawn);
    m_lua.Register("remove", this, &WorldObjectBindings::apiRemove);

    m_lua.Register("position", this, &WorldObjectBindings::apiPosition);
    m_lua.Register("orientation", this, &WorldObjectBindings::apiOrientation);
    m_lua.Register("setPosition", this, &WorldObjectBindings::apiSetPosition);
    m_lua.Register("setOrientation", this, &WorldObjectBindings::apiSetOrientation);
    m_lua.Register("setShowOnHud", this, &WorldObjectBindings::apiSetShowOnHud);
    m_lua.Register("setCanLockOn", this, &WorldObjectBindings::apiSetCanLockOn);

    m_lua.Register("onWorldObjectDestroyed", this, &WorldObjectBindings::apiOnWorldObjectDestroyed);
    m_lua.Register("onAABBEntered", this, &WorldObjectBindings::apiOnAABBEntered);
}

apikey WorldObjectBindings::apiPlayerShip() {
    if (m_script.universe()->player().ship()) {
        return m_script.universe()->player().ship()->scriptKey();
    } else {
        return 0;
    }
}

apikey WorldObjectBindings::apiCreateShip(const std::string& name) {
    Ship* ship = WorldObjectBuilder(name).buildShip();

    if (!ship) {
        glow::warning("WorldObjectBindings: Couldn't create ship '%;'", name);
        return -1;
    }

    m_scriptEngine.registerScriptable(ship);

    return ship->scriptKey();
}

apikey WorldObjectBindings::apiCreateWorldObject(const std::string& name) {
    WorldObject* worldObject = WorldObjectBuilder(name).buildWorldObject();

    if (!worldObject) {
        glow::warning("WorldObjectBindings: Couldn't create worldObject '%;'", name);
        return -1;
    }

    m_scriptEngine.registerScriptable(worldObject);

    return worldObject->scriptKey();
}

int WorldObjectBindings::apiSpawn(apikey worldObjectKey, const std::string& sectorName) {
    WorldObject* worldObject = m_scriptEngine.get<WorldObject>(worldObjectKey);

    if (!worldObject) {
        return -1;
    }

    Sector* sector = m_script.universe()->sector(sectorName);
    worldObject->spawn(sector);

    return worldObject->spawnState() == SpawnState::Spawned;
}

int WorldObjectBindings::apiRemove(apikey worldObjectKey) {
    WorldObject* worldObject = m_scriptEngine.get<WorldObject>(worldObjectKey);

    if (!worldObject) {
        return -1;
    }

    worldObject->scheduleRemoval();

    return 0;
}

glm::vec3 WorldObjectBindings::apiOrientation(apikey worldObjectKey) {
    WorldObject* worldObject = m_scriptEngine.get<WorldObject>(worldObjectKey);

    if (!worldObject) {
        return glm::vec3(0.0f);
    }

    return glm::eulerAngles(worldObject->transform().orientation());
}

glm::vec3 WorldObjectBindings::apiPosition(apikey worldObjectKey) {
    WorldObject* worldObject = m_scriptEngine.get<WorldObject>(worldObjectKey);

    if (!worldObject) {
        return glm::vec3(0.0f);
    }

    return worldObject->transform().position();
}

int WorldObjectBindings::apiSetPosition(apikey worldObjectKey, const glm::vec3& position) {
    WorldObject* worldObject = m_scriptEngine.get<WorldObject>(worldObjectKey);

    if (!worldObject) {
        return -1;
    }

    worldObject->transform().setPosition(position);

    return 0;
}

int WorldObjectBindings::apiSetOrientation(apikey worldObjectKey, const glm::vec3& orientation) {
    WorldObject* worldObject = m_scriptEngine.get<WorldObject>(worldObjectKey);

    if (!worldObject) {
        return -1;
    }

    worldObject->transform().setOrientation(glm::quat(orientation));
    return 0;
}

int WorldObjectBindings::apiSetShowOnHud(apikey worldObjectKey, bool show) {
    WorldObject* worldObject = m_scriptEngine.get<WorldObject>(worldObjectKey);

    if (!worldObject) {
        return -1;
    }

    worldObject->info().setShowOnHud(true);
    return 0;
}

int WorldObjectBindings::apiSetCanLockOn(apikey worldObjectKey, bool lockon) {
    WorldObject* worldObject = m_scriptEngine.get<WorldObject>(worldObjectKey);

    if (!worldObject) {
        return -1;
    }

    worldObject->info().setCanLockOn(lockon);
    return 0;
}

apikey WorldObjectBindings::apiOnWorldObjectDestroyed(apikey key, const std::string& callback) {
    WorldObject* worldObject = m_scriptEngine.get<WorldObject>(key);

    if (!worldObject) {
        return -1;
    }

    auto destructionPoll = new WorldObjectDestroyedPoll(worldObject, createCallback(callback, key));
    destructionPoll->spawn(m_script.universe());

    return destructionPoll->scriptKey();
}

apikey WorldObjectBindings::apiOnAABBEntered(apikey key, const glm::vec3& llf, const glm::vec3& urb, const std::string& sectorName, const std::string& callback) {
    WorldObject* worldObject = m_scriptEngine.get<WorldObject>(key);

    if (!worldObject) {
        return -1;
    }

    Sector* sector = m_script.universe()->sector(sectorName);

    if (sector) {
        auto enteredPoll = new AABBEnteredPoll(worldObject, AABB(llf, urb), createCallback(callback, key));
        enteredPoll->spawn(sector);

        return enteredPoll->scriptKey();
    } else {
        return Scriptable::INVALID_KEY;
    }
}

