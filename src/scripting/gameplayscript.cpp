#include "gameplayscript.h"

#include <iostream>

#include <glow/logging.h>

#include "bindings/worldobjectbindings.h"
#include "bindings/aibindings.h"

#include "events/eventpoller.h"
#include "events/singleshottimer.h"
#include "events/loopingtimer.h"
#include "events/aabbenteredpoll.h"

#include "gamestate/gameplay/gameplay.h"

#include "geometry/aabb.h"

#include "scripting/elematelua/luawrapper.h"
#include "scripting/scriptengine.h"

#include "world/world.h"
#include "worldobject/worldobject.h"



GamePlayScript::GamePlayScript(GamePlay* gamePlay, ScriptEngine* scriptEngine) :
    Script(),
    m_gamePlay(gamePlay),
    m_scriptEngine(scriptEngine),
    m_bindings()
{
    m_bindings.push_back(std::unique_ptr<WorldObjectBindings>(new WorldObjectBindings(*this)));
    m_bindings.push_back(std::unique_ptr<AiBindings>(new AiBindings(*this)));
    initializeBindings();
} 


GamePlayScript::~GamePlayScript() = default;

void GamePlayScript::initializeBindings() {

    m_lua->Register("valid", this, &GamePlayScript::apiValid);
    m_lua->Register("showText", this, &GamePlayScript::apiShowText);
    m_lua->Register("showTextFor", this, &GamePlayScript::apiShowTextFor);
    
    m_lua->Register("setActive", this, &GamePlayScript::apiSetEventActive);

    m_lua->Register("createSingleShotTimer", this, &GamePlayScript::apiCreateSingleShotTimer);
    m_lua->Register("createLoopingTimer", this, &GamePlayScript::apiCreateLoopingTimer);

    m_lua->Register("onAABBEntered", this, &GamePlayScript::apiOnAABBEntered);

    for (auto& bindings : m_bindings) {
        bindings->initialize();
    }

}


int GamePlayScript::apiSetEventActive(int key, bool active) {
    EventPoll* poll = m_scriptEngine->get<EventPoll>(key);

    if (!poll) {
        return -1;
    }

    poll->setActive(active);
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

bool GamePlayScript::apiValid(int key) {
    return m_scriptEngine->get<void>(key) != nullptr;
}

int GamePlayScript::apiShowText(const std::string& string) {
    return apiShowTextFor(string, 3);
}


int GamePlayScript::apiShowTextFor(const std::string& string, int seconds) {
    // TODO show text on hud
    glow::debug("Script: %; [%;s]", string, seconds);
    return 0;
}

ScriptEngine& GamePlayScript::scriptEngine() {
    return *m_scriptEngine;
}

GamePlay& GamePlayScript::gamePlay() {
    return *m_gamePlay;
}

LuaWrapper& GamePlayScript::luaWrapper() {
    return *m_lua;
}
