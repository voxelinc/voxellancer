#include "aibindings.h"

#include "ai/basictasks/flytotask.h"
#include "ai/basictasks/fighttask.h"
#include "ai/boardcomputer.h"
#include "ai/character.h"

#include "events/aitaskfinishedpoll.h"
#include "events/eventpoller.h"

#include "factions/faction.h"
#include "factions/factionmatrix.h"
#include "factions/factionrelation.h"

#include "scripting/gameplayscript.h"
#include "scripting/scriptengine.h"
#include "scripting/elematelua/luawrapper.h"
#include "scripting/scriptcallback.h"
#include "scripting/scriptengine.h"
#include "scripting/gameplayscript.h"

#include "worldobject/ship.h"
#include "world/world.h"


AiBindings::AiBindings(GamePlayScript& script):
    Bindings(script)
{

}

void AiBindings::bind() {
    m_lua.Register("getFaction", this, &AiBindings::apiGetFaction);
    m_lua.Register("setFaction", this, &AiBindings::apiGetFaction);
    m_lua.Register("getFactionRelation", this, &AiBindings::apiGetFactionRelation);
    m_lua.Register("setFactionRelation", this, &AiBindings::apiSetFactionRelation);

    m_lua.Register("onAiTaskFinished", this, &AiBindings::apiOnAiTaskFinished);

    m_lua.Register("createFlyToTask", this, &AiBindings::apiCreateFlyToTask);
    m_lua.Register("setTargetPoint", this, &AiBindings::apiSetTargetPoint);
    m_lua.Register("createFightTask", this, &AiBindings::apiCreateFightTask);
    m_lua.Register("addFightTaskTarget", this, &AiBindings::apiAddFightTaskTarget);

    m_lua.Register("taskExecutor", this, &AiBindings::apiTaskExecutor);
}


std::string AiBindings::apiGetFaction(apikey key) {
    Ship* ship = m_scriptEngine.get<Ship>(key);

    if (!ship) {
        glow::warning("AiBindings: ship %; doesnt exist", key);
        return "";
    }

    return ship->character()->faction()->key();
}

int AiBindings::apiSetFaction(apikey key, const std::string& faction) {
    Ship* ship = m_scriptEngine.get<Ship>(key);

    if (!ship) {
        glow::warning("AiBindings: ship %; doesnt exist", key);
        return -1;
    }

    Faction& f = World::instance()->factionMatrix().getFaction(faction);
    ship->character()->setFaction(&f);
    return 0;
}

float AiBindings::apiGetFactionRelation(const std::string& factionA, const std::string& factionB) {
    FactionMatrix& factions = World::instance()->factionMatrix();
    Faction& fA = factions.getFaction(factionA);
    Faction& fB = factions.getFaction(factionB);
    return factions.getRelation(fA, fB).friendliness();
}

int AiBindings::apiSetFactionRelation(const std::string& factionA, const std::string& factionB, float friendliness) {
    FactionMatrix& factions = World::instance()->factionMatrix();
    Faction& fA = factions.getFaction(factionA);
    Faction& fB = factions.getFaction(factionB);
    factions.getRelation(fA, fB).setFriendliness(friendliness);
    return 0;
}

apikey AiBindings::apiOnAiTaskFinished(apikey key, const std::string& callback) {
    AiTask* aiTask = m_scriptEngine.get<AiTask>(key);

    if (!aiTask) {
        glow::warning("AiBindings: AiTask '%;' doesn't exist", key);
        return -1;
    }

    auto finishedPoll = std::make_shared<AiTaskFinishedPoll>(aiTask, createCallback(callback, key));

    World::instance()->eventPoller().addPoll(finishedPoll);
    m_script.addLocal(finishedPoll);

    return finishedPoll->scriptKey();
}

apikey AiBindings::apiCreateFlyToTask(apikey key) {
    Ship* ship = m_scriptEngine.get<Ship>(key);

    if (!ship) {
        glow::warning("AiBindings: Ship '%;' doesn't exist", key);
        return -1;
    }

    auto flyToTask = std::make_shared<FlyToTask>(ship->boardComputer());
    m_scriptEngine.registerScriptable(flyToTask.get());

    Character* character = ship->character();
    if (!character) {
        glow::warning("AiBindings: Ship '%;' has no Character", key);
        return -1;
    }
    character->setTask(flyToTask);

    return flyToTask->scriptKey();
}

int AiBindings::apiSetTargetPoint(apikey key, const glm::vec3& point) {
    FlyToTask* flyToTask = m_scriptEngine.get<FlyToTask>(key);

    if (!flyToTask) {
        glow::warning("AiBindings: FlyToTask '%;' doesn't exist", key);
        return -1;
    }

    flyToTask->setTargetPoint(point);
    return 0;
}

apikey AiBindings::apiCreateFightTask(apikey key) {
    Ship* ship = m_scriptEngine.get<Ship>(key);

    if (!ship) {
        glow::warning("AiBindings: Ship '%;' doesn't exist", key);
        return -1;
    }

    FightTask* fightTask = new FightTask(ship->boardComputer(), {});

    m_scriptEngine.registerScriptable(fightTask);

    Character* character = ship->character();
    character->setTask(std::shared_ptr<AiTask>(fightTask));

    return fightTask->scriptKey();
}


int AiBindings::apiAddFightTaskTarget(apikey key, apikey worldObjectKey) {
    FightTask* fightTask = m_scriptEngine.get<FightTask>(key);

    if (!fightTask) {
        glow::warning("AiBindings: Fighttask '%;' doesn't exist", key);
        return -1;
    }

    WorldObject* worldObject = m_scriptEngine.get<WorldObject>(worldObjectKey);
    if (!worldObject){
        return -1;
    }

    fightTask->addTarget(makeHandle(worldObject));
    return 0;
}

apikey AiBindings::apiTaskExecutor(apikey aiTask) {
    AiTask* task = m_scriptEngine.get<AiTask>(aiTask);

    if (!task) {
        glow::warning("AiBindings: AiTask '%;' doesn't exist", aiTask);
        return -1;
    }

    assert(task->boardComputer());
    WorldObject* ship = task->boardComputer()->worldObject();
    assert(ship);

    return ship->scriptKey();
}

