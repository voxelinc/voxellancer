#include "missionscript.h"

#include <iostream>

#include "bindings/internalmissionbindings.h"

#include "scripting/scriptengine.h"
#include "scripting/elematelua/luawrapper.h"

#include "missions/mission.h"


MissionScript::MissionScript(Mission& mission, ScriptEngine& scriptEngine):
    GamePlayScript(scriptEngine),
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

void MissionScript::doSpawn() {
    m_scriptEngine->registerScriptable(this);
    // do not register in sector or universe, MissionScripts are managed by their mission
}

void MissionScript::doUnspawn() {
    m_scriptEngine->unregisterScriptable(this);
}

