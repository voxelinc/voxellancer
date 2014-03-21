#include "gameplayscript.h"

#include <glow/logging.h>

#include "bindings/worldobjectbindings.h"
#include "bindings/aibindings.h"
#include "bindings/commonbindings.h"
#include "bindings/squadbindings.h"


GamePlayScript::GamePlayScript(ScriptEngine* scriptEngine):
    m_scriptEngine(scriptEngine)
{
    addBindings(new CommonBindings(*this));
    addBindings(new WorldObjectBindings(*this));
    addBindings(new AiBindings(*this));
    addBindings(new SquadBindings(*this));
}

GamePlayScript::~GamePlayScript() = default;

ScriptEngine& GamePlayScript::scriptEngine() {
    return *m_scriptEngine;
}

LuaWrapper& GamePlayScript::luaWrapper() {
    return *m_lua;
}

