#include "scriptengine.h"

#include <algorithm>

#include "scripting/gameplayscript.h"


ScriptEngine::ScriptEngine(World* world):
    m_world(world),
    m_eventPollHandleIncrementor(0)
{
}

void ScriptEngine::startScript(GamePlayScript* script) {
    m_scripts.push_back(script);
    script->start();
}

void ScriptEngine::registerTimer(Timer *timer) {
    m_timerManager.registerTimer(timer);
}

int ScriptEngine::registerEventPoll(EventPoll* eventPoll) {
    m_eventPolls[m_eventPollHandleIncrementor].reset(eventPoll);
    return m_eventPollHandleIncrementor++;
}

void ScriptEngine::unregisterEventPoll(int handle) {
    m_eventPolls.erase(handle);
}

void ScriptEngine::update(float deltaSec) {
    m_timerManager.update(deltaSec);

    for(std::pair<const int, std::unique_ptr<EventPoll>>& pair : m_eventPolls) {
        pair.second->update(deltaSec);
    }
}

