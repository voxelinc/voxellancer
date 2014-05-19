#include "internalmissionbindings.h"

#include <iostream>

#include "missions/mission.h"

#include "scripting/elematelua/luawrapper.h"
#include "scripting/missionscript.h"

#include "ui/hud/hud.h"

#include "universe/universe.h"

#include "player.h"


InternalMissionBindings::InternalMissionBindings(MissionScript& script):
    Bindings(script),
    m_missionScript(script)
{

}

void InternalMissionBindings::bind() {
    m_lua.Register("missionSucceed", this, &InternalMissionBindings::apiMissionSucceed);
    m_lua.Register("missionFail", this, &InternalMissionBindings::apiMissionFail);
    m_lua.Register("missionMessage", this, &InternalMissionBindings::apiMissionMessage);
    m_lua.Register("missionFailureMessage", this, &InternalMissionBindings::apiMissionFailureMessage);
    m_lua.Register("missionSuccessMessage", this, &InternalMissionBindings::apiMissionSuccessMessage);
}

int InternalMissionBindings::apiMissionSucceed() {
    if (m_missionScript.mission().state() == MissionState::Running) {
        m_missionScript.mission().succeed();
        return 0;
    } else {
        glow::warning("InternalMissionBindings: Mission not running, can't succeed");
        return -1;
    }
}

int InternalMissionBindings::apiMissionFail() {
    if (m_missionScript.mission().state() == MissionState::Running) {
        m_missionScript.mission().fail();
        return 0;
    } else {
        glow::warning("InternalMissionBindings: Mission not running, can't fail");
        return -1;
    }
}

int InternalMissionBindings::apiMissionMessage(const std::string& message) {
    m_script.universe()->player().hud().showMissionMessage(message);
    return 0;
}

int InternalMissionBindings::apiMissionFailureMessage(const std::string& message) {
    m_script.universe()->player().hud().showMissionMessage(message);
    return 0;
}

int InternalMissionBindings::apiMissionSuccessMessage(const std::string& message) {
    m_script.universe()->player().hud().showMissionMessage(message);
    return 0;
}

