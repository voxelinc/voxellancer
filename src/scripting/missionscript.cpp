#include "missionscript.h"

#include "bindings/missionbindings.h"

#include "scripting/elematelua/luawrapper.h"


MissionScript::MissionScript(Mission& mission, ScriptEngine* scriptEngine):
    GamePlayScript(scriptEngine),
    m_mission(mission)
{
    addBindings(new MissionBindings(*this));
}

Mission& MissionScript::mission() {
    return m_mission;
}

void MissionScript::onSuccess() {
    if (m_lua->has("onSuccess")) {
        m_lua->call("onSuccess");
    }
}

void MissionScript::onFailure() {
    if (m_lua->has("onFailure")) {
        m_lua->call("onFailure");
    }
}

