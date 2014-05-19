#include "gameplayscript.h"

#include <glow/logging.h>

#include "bindings/worldobjectbindings.h"
#include "bindings/aibindings.h"
#include "bindings/externalmissionbindings.h"
#include "bindings/commonbindings.h"
#include "bindings/squadbindings.h"

#include "events/eventpoll.h"

#include "scripting/scriptable.h"
#include "scripting/scriptengine.h"


GamePlayScript::GamePlayScript(ScriptEngine& scriptEngine):
    m_scriptEngine(&scriptEngine)
{
    addGamePlayBindings();
}

GamePlayScript::~GamePlayScript() = default;

ScriptEngine& GamePlayScript::scriptEngine() {
    return *m_scriptEngine;
}

LuaWrapper& GamePlayScript::luaWrapper() {
    return *m_lua;
}

void GamePlayScript::addGamePlayBindings() {
    addBindings(new CommonBindings(*this));
    addBindings(new WorldObjectBindings(*this));
    addBindings(new AiBindings(*this));
    addBindings(new SquadBindings(*this));
    addBindings(new ExternalMissionBindings(*this));
}

