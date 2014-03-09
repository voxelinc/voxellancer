#include "scriptengine.h"

#include <algorithm>
#include <iostream>

#include <glow/logging.h>

#include "ai/aitask.h"

#include "events/eventpoll.h"

#include "worldobject/ship.h"
#include "worldobject/worldobject.h"

#include "gameplayscript.h"
#include "scriptable.h"


ScriptEngine::ScriptEngine(World* world):
    m_world(world),
    m_keyIncrementor(1),
    m_running(false)
{
}

ScriptEngine::~ScriptEngine() = default;

void ScriptEngine::addScript(std::shared_ptr<GamePlayScript> script) {
    m_scripts.push_back(script);
    if (m_running) {
        script->start();
    }
}

void ScriptEngine::start() {
    m_running = true;
    for (std::shared_ptr<GamePlayScript>& script : m_scripts) {
        if (!script->started()) {
            script->start();
        }
    }
}

void ScriptEngine::stop() {
    m_running = false;
}

void ScriptEngine::registerScriptable(Scriptable* scriptable) {
    if (scriptable->scriptKey() > 0) {
        // This is legit indeed and happens when an object is created by a script
        return;
    }

    m_scriptables[m_keyIncrementor] = scriptable;
    scriptable->setScriptKey(m_keyIncrementor);

    m_keyIncrementor++;
}

void ScriptEngine::unregisterScriptable(Scriptable* scriptable) {
    if (scriptable->scriptKey() > 0) {
        m_scriptables.erase(scriptable->scriptKey());
        scriptable->setScriptKey(Scriptable::INVALID_KEY);
    }
}

Scriptable* ScriptEngine::getScriptable(int key) {
    if (key <= 0 || key >= m_keyIncrementor) {
        glow::warning("ScriptEngine: script-key '%;' is not valid", key);
        return nullptr;
    } else {
        auto pair = m_scriptables.find(key);
        if (pair == m_scriptables.end()) {
            glow::warning("ScriptEngine: the script-key '%;' points to a removed object, next time check with valid()", key);
            return nullptr;
        } else {
            return pair->second;
        }
    }
}

void ScriptEngine::update(float deltaSec) {

}

