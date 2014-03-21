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
    m_lua.Register("missionSucceeded", this, &MissionBindings::apiMissionSucceeded);
    m_lua.Register("missionFailed", this, &MissionBindings::apiMissionFailed);
    m_lua.Register("missionMessage", this, &MissionBindings::apiMissionMessage);
    m_lua.Register("missionFailureMessage", this, &MissionBindings::apiMissionFailureMessage);
    m_lua.Register("missionSuccessMessage", this, &MissionBindings::apiMissionSuccessMessage);
}

int MissionBindings::apiMissionSucceeded() {
    m_missionScript.mission().succeeded();
}

int MissionBindings::apiMissionFailed() {
    m_missionScript.mission().failed();
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

