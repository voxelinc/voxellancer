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

void ScriptEngine::update(float deltaSec) {

}
