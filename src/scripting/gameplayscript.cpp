#include "gameplayscript.h"

#include <glow/logging.h>

#include "bindings/worldobjectbindings.h"
#include "bindings/aibindings.h"
#include "bindings/commonbindings.h"
#include "bindings/squadbindings.h"

#include "scripting/scriptable.h"


GamePlayScript::GamePlayScript(ScriptEngine* scriptEngine):
    m_scriptEngine(scriptEngine)
{
    addBindings(new CommonBindings(*this));
    addBindings(new WorldObjectBindings(*this));
    addBindings(new AiBindings(*this));
    addBindings(new SquadBindings(*this));
}

GamePlayScript::~GamePlayScript() {
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

void GamePlayScript::addLocal(int key) {
    assert(m_scriptEngine->keyValid(key));

    m_scriptEngine->get<Scriptable>(key)->setScriptLocal(true);
    m_locals.push_back(key);
}

