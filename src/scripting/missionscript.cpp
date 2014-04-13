#include "missionscript.h"

#include <iostream>

#include "bindings/internalmissionbindings.h"

#include "scripting/elematelua/luawrapper.h"

#include "missions/mission.h"


MissionScript::MissionScript(Mission& mission, ScriptEngine& scriptEngine):
    GamePlayScript(scriptEngine, &mission),
    m_mission(mission)
{
    addBindings(new InternalMissionBindings(*this));
}

Mission& MissionScript::mission() {
    return m_mission;
}

void MissionScript::onSuccess() {
    if (m_lua->hasFunction("onSuccess")) {
        m_lua->call("onSuccess");
    }
}

void MissionScript::onFailure() {
    if (m_lua->hasFunction("onFailure")) {
        m_lua->call("onFailure");
     }
}

