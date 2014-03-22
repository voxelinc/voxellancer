#include "missionbindings.h"

#include <iostream>

#include "missions/mission.h"

#include "scripting/elematelua/luawrapper.h"
#include "scripting/missionscript.h"

#include "ui/hud/hud.h"

#include "world/world.h"

#include "player.h"


MissionBindings::MissionBindings(MissionScript& script):
    Bindings(script),
    m_missionScript(script)
{

}

void MissionBindings::bind() {
    m_lua.Register("missionSucceed", this, &MissionBindings::apiMissionSucceed);
    m_lua.Register("missionFail", this, &MissionBindings::apiMissionFail);
    m_lua.Register("missionMessage", this, &MissionBindings::apiMissionMessage);
    m_lua.Register("missionFailureMessage", this, &MissionBindings::apiMissionFailureMessage);
    m_lua.Register("missionSuccessMessage", this, &MissionBindings::apiMissionSuccessMessage);
}

int MissionBindings::apiMissionSucceed() {
    if (m_missionScript.mission().active()) {
        m_missionScript.mission().succeed();
    } else {
        glow::warning("MissionBindings: Mission already marked as succeed");
    }
}

int MissionBindings::apiMissionFail() {
    if (m_missionScript.mission().active()) {
        m_missionScript.mission().fail();
    } else {
        glow::warning("MissionBindings: Mission already marked as failure");
    }
}

int MissionBindings::apiMissionMessage(const std::string& message) {
    World::instance()->player().hud().showMissionMessage(message);
}

int MissionBindings::apiMissionFailureMessage(const std::string& message) {
    World::instance()->player().hud().showMissionMessage(message);
}

int MissionBindings::apiMissionSuccessMessage(const std::string& message) {
    World::instance()->player().hud().showMissionMessage(message);
}

