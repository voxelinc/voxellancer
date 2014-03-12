#include "aibindings.h"

#include "ai/basictasks/flytotask.h"
#include "ai/character.h"

#include "events/aitaskfinishedpoll.h"
#include "events/eventpoller.h"

#include "factions/faction.h"
#include "factions/factionmatrix.h"
#include "factions/factionrelation.h"

#include "scripting/scriptengine.h"
#include "scripting/elematelua/luawrapper.h"

#include "worldobject/ship.h"
#include "world/world.h"




AiBindings::AiBindings(GamePlayScript& script): 
    Bindings(script)
{

}

void AiBindings::initialize() {
    m_lua.Register("createFlyToTask", this, &AiBindings::apiCreateFlyToTask);
    m_lua.Register("setTargetPoint", this, &AiBindings::apiSetTargetPoint);

}


std::string AiBindings::apiGetFaction(apikey key) {
    Ship* ship = m_scriptEngine.get<Ship>(key);

    if (!ship) { 
        glow::warning("AiBindings: ship %; doesnt exist", key);
        return ""; 
    }

    return ship->character()->faction().key();
}

int AiBindings::apiSetFaction(apikey key, const std::string& faction) {
    Ship* ship = m_scriptEngine.get<Ship>(key);

    if (!ship) {
        glow::warning("AiBindings: ship %; doesnt exist", key);
        return -1;
    }
    
    Faction& f = World::instance()->factionMatrix().getFaction(faction);
    ship->character()->setFaction(f);
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


apikey AiBindings::onAiTaskFinished(apikey key, const std::string& callback) {
    AiTask* aiTask = m_scriptEngine.get<AiTask>(key);

    if (!aiTask) { return -1; }

    auto finishedPoll = std::make_shared<AiTaskFinishedPoll>(aiTask, [=] { m_lua.call(callback, key); });
    World::instance()->eventPoller().addPoll(finishedPoll);
    return finishedPoll->scriptKey();
}


apikey AiBindings::apiCreateFlyToTask(apikey key) {
    Ship* ship = m_scriptEngine.get<Ship>(key);

    if (!ship) { return -1; }

    FlyToTask* flyToTask = new FlyToTask(ship->boardComputer());

    m_scriptEngine.registerScriptable(flyToTask);

    Character* character = ship->character();
    if (!character) {
        glow::warning("AiBindings: Ship '%;' has no Character", key);
        return -1;
    }
    character->setTask(std::shared_ptr<AiTask>(flyToTask));

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
