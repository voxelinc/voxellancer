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
    m_handleKeyIncrementor(1),
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

    m_handles[m_handleKeyIncrementor] = scriptable;
    scriptable->setScriptKey(m_handleKeyIncrementor);

    m_handleKeyIncrementor++;
}

void ScriptEngine::unregisterScriptable(Scriptable* scriptable) {
    if (scriptable->scriptKey() > 0) {
        m_handles.erase(scriptable->scriptKey());
    }
}

Scriptable* ScriptEngine::getScriptable(int key) {
    if (key <= 0 || key >= m_handleKeyIncrementor) {
        glow::warning("ScriptEngine: script-key '%;' is not valid", key);
        return nullptr;
    } else {
        auto pair = m_handles.find(key);
        if (pair == m_handles.end()) {
            glow::warning("ScriptEngine: the script-key '%;' points to a removed object, next time check with valid()", key);
            return nullptr;
        } else {
            return pair->second;
        }
    }
}

void ScriptEngine::update(float deltaSec) {
//    m_timerManager.update(deltaSec);

//    for(std::pair<const int, std::unique_ptr<EventPoll>>& pair : m_eventPolls) {
//        pair.second->update(deltaSec);
//    }
}

