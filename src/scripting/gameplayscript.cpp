#include "gameplayscript.h"

#include <glow/logging.h>

#include "bindings/worldobjectbindings.h"
#include "bindings/aibindings.h"
#include "bindings/externalmissionbindings.h"
#include "bindings/commonbindings.h"
#include "bindings/squadbindings.h"

#include "events/eventpoll.h"
#include "events/eventpoller.h"

#include "scripting/scriptable.h"
#include "scripting/scriptengine.h"

#include "world/world.h"


GamePlayScript::GamePlayScript(ScriptEngine& scriptEngine):
    m_scriptEngine(&scriptEngine)
{
    addGamePlayBindings();
}

GamePlayScript::~GamePlayScript() {
    for (std::weak_ptr<EventPoll>& eventPoll : m_eventPolls) {
        if (auto poll = eventPoll.lock()) {
            World::instance()->eventPoller().removePoll(poll.get());
        }
    }

    for (int key : m_locals) {
        if (m_scriptEngine->keyValid(key)) {
            m_scriptEngine->unregisterScriptable(m_scriptEngine->get<Scriptable>(key));
        }
    }
}

ScriptEngine& GamePlayScript::scriptEngine() {
    return *m_scriptEngine;
}

LuaWrapper& GamePlayScript::luaWrapper() {
    return *m_lua;
}

void GamePlayScript::addLocal(std::shared_ptr<EventPoll> poll) {
    m_eventPolls.push_back(poll);
    addLocal(poll.get());
}

void GamePlayScript::addLocal(Scriptable* scriptable) {
    assert(m_scriptEngine->keyValid(scriptable->scriptKey()));

    scriptable->setScriptLocal(true);
    m_locals.push_back(scriptable->scriptKey());
}

void GamePlayScript::addGamePlayBindings() {
    addBindings(new CommonBindings(*this));
    addBindings(new WorldObjectBindings(*this));
    addBindings(new AiBindings(*this));
    addBindings(new SquadBindings(*this));
    addBindings(new ExternalMissionBindings(*this));
}

