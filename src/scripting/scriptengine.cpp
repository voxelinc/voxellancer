#include "scriptengine.h"

#include "scripting/gameplayscript.h"


ScriptEngine::ScriptEngine(World* world):
    m_world(world)
{
}

void ScriptEngine::startScript(GamePlayScript* script) {
    m_scripts.push_back(script);
    script->start();
}

void ScriptEngine::registerTimer(Timer *timer) {
    m_timerManager.registerTimer(timer);
}

void ScriptEngine::update(float deltaSec) {
    m_timerManager.update(deltaSec);
}

