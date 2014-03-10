#include "gameplayscript.h"

#include <iostream>

#include <glow/logging.h>

#include "bindings/worldobjectbindings.h"
#include "bindings/aibindings.h"
#include "bindings/commonbindings.h"
#include "bindings/squadbindings.h"

GamePlayScript::GamePlayScript(GamePlay* gamePlay, ScriptEngine* scriptEngine):
    m_gamePlay(gamePlay),
    m_scriptEngine(scriptEngine),
    m_bindings()
{
    m_bindings.push_back(std::unique_ptr<CommonBindings>(new CommonBindings(*this)));
    m_bindings.push_back(std::unique_ptr<WorldObjectBindings>(new WorldObjectBindings(*this)));
    m_bindings.push_back(std::unique_ptr<AiBindings>(new AiBindings(*this)));
    m_bindings.push_back(std::unique_ptr<SquadBindings>(new SquadBindings(*this)));

    for (auto& bindings : m_bindings) {
        bindings->initialize();
    }
} 


GamePlayScript::~GamePlayScript() = default;

void GamePlayScript::initializeBindings() {
    

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
