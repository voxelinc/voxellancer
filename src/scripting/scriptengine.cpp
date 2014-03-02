#include "scriptengine.h"

#include <algorithm>
#include <iostream>

#include <glow/logging.h>

#include "events/eventpoll.h"

#include "worldobject/ship.h"
#include "worldobject/worldobject.h"

#include "gameplayscript.h"
#include "scriptable.h"
#include "scripthandle.h"


ScriptEngine::ScriptEngine(World* world):
    m_world(world),
    m_handleKeyIncrementor(0),
    m_running(false)
{
}

ScriptEngine::~ScriptEngine() = default;

void ScriptEngine::addScript(GamePlayScript* script) {
    m_scripts.push_back(std::unique_ptr<GamePlayScript>(script));
    if (m_running) {
        script->start();
    }
}

void ScriptEngine::start() {
    m_running = true;
    for (std::unique_ptr<GamePlayScript>& script : m_scripts) {
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

    m_handles.resize(m_handleKeyIncrementor + 1);

    IScriptHandle* scriptHandle = nullptr;
    switch(scriptable->scriptableType()) {
        case ScriptableType::WorldObject:
            scriptHandle = new ScriptHandle<WorldObject>(dynamic_cast<WorldObject*>(scriptable));
        break;
        case ScriptableType::Ship:
            scriptHandle = new ScriptHandle<Ship>(dynamic_cast<Ship*>(scriptable));
        break;
        case ScriptableType::EventPoll:
            scriptHandle = new ScriptHandle<EventPoll>(dynamic_cast<EventPoll*>(scriptable));
        break;
        default:
            assert(0);
    }
    m_handles[m_handleKeyIncrementor].reset(scriptHandle);

    scriptable->setScriptKey(m_handleKeyIncrementor);

    m_handleKeyIncrementor++;
}

void ScriptEngine::unregisterScriptable(Scriptable* scriptable) {
    if (scriptable->scriptKey() > 0) {
        m_handles[scriptable->scriptKey()]->invalidate();
    }
}

Scriptable* ScriptEngine::getScriptable(int key) {
    if (key < 0 || key >= m_handles.size()) {
        glow::warning("ScriptEngine: script-key '%;' is not valid", key);
        return nullptr;
    } else {
        Scriptable* scriptable = m_handles[key]->scriptable();
        if (!scriptable) {
            glow::warning("ScriptEngine: the script-key '%;' points to a removed object, next time check with valid()", key);
            return nullptr;
        } else {
            return scriptable;
        }
    }
}

WorldObject* ScriptEngine::getWorldObject(int key) {
    Scriptable* scriptable = getScriptable(key);
    if (!scriptable) {
        return nullptr;
    }

    if (scriptable->scriptableType() == ScriptableType::WorldObject || scriptable->scriptableType() == ScriptableType::Ship) {
        return static_cast<WorldObject*>(scriptable);
    } else {
        glow::warning("ScriptEngine: script-key '%;' of type '%;' is no WorldObject", key, static_cast<int>(scriptable->scriptableType()));
        return nullptr;
    }
}

EventPoll* ScriptEngine::getEventPoll(int key) {
    Scriptable* scriptable = getScriptable(key);
    if (!scriptable) {
        return nullptr;
    }

    if (scriptable->scriptableType() == ScriptableType::EventPoll) {
        return static_cast<EventPoll*>(scriptable);
    } else {
        glow::warning("ScriptEngine: script-key '%;' of type '%;' is no EventPoll", key, static_cast<int>(scriptable->scriptableType()));
        return nullptr;
    }
}

//void ScriptEngine::registerTimer(Timer *timer) {
//    m_timerManager.registerTimer(timer);
//}
//
//int ScriptEngine::registerWorldObject(WorldObject* worldObject) {
//    std::shared_ptr<WorldObjectScriptHandle> handle = std::make_shared<WorldObjectScriptHandle>(m_worldObjectHandleIncrementor, worldObject);
//
//    m_handle2WorldObjectHandle.insert({
//        m_worldObjectHandleIncrementor,
//        handle
//    });
//    m_worldObject2WorldObjectHandle.insert({
//        worldObject,
//        handle
//    });
//
//    return m_worldObjectHandleIncrementor++;
//}
//
//WorldObject* ScriptEngine::getWorldObject(int handle) {
//    auto i = m_handle2WorldObjectHandle.find(handle);
//    if (i == m_handle2WorldObjectHandle.end() || !i->second->valid()) {
//        glow::info("ScriptEngine: Trying to access invalid WorldObject-Handle %;", handle);
//        return nullptr;
//    } else {
//        return i->second->worldObject();
//    }
//}
//
//int ScriptEngine::getWorldObjectHandle(WorldObject* worldObject) {
//    auto i = m_worldObject2WorldObjectHandle.find(worldObject);
//    if (i == m_worldObject2WorldObjectHandle.end() || !i->second->valid()) {
//        return -1;
//    } else {
//        return i->second->key();
//    }
//}
//
//void ScriptEngine::addWorldObject(WorldObject* worldObject) {
//    int handle = getWorldObjectHandle(worldObject);
//    if (handle < 0) {
//        registerWorldObject(worldObject);
//    }
//}
//
//void ScriptEngine::removeWorldObject(WorldObject* worldObject) {
//    int handle = getWorldObjectHandle(worldObject);
//    assert(handle > 0);
//
//    m_handle2WorldObjectHandle.erase(handle);
//    m_worldObject2WorldObjectHandle.erase(worldObject);
//}
//
//int ScriptEngine::registerEventPoll(EventPoll* eventPoll) {
//    m_eventPolls[m_eventPollHandleIncrementor].reset(eventPoll);
//    return m_eventPollHandleIncrementor++;
//}
//
//void ScriptEngine::unregisterEventPoll(int handle) {
//    m_eventPolls.erase(handle);
//}

void ScriptEngine::update(float deltaSec) {
//    m_timerManager.update(deltaSec);

//    for(std::pair<const int, std::unique_ptr<EventPoll>>& pair : m_eventPolls) {
//        pair.second->update(deltaSec);
//    }
}

