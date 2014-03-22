#include "externalmissionbindings.h"

#include "missions/mission.h"

#include "scripting/elematelua/luawrapper.h"

#include "world/world.h"

#include "player.h"


ExternalMissionBindings::ExternalMissionBindings(GamePlayScript& script):
    Bindings(script)
{

}

void ExternalMissionBindings::bind() {
    m_lua.Register("missionStart", this, &ExternalMissionBindings::apiMissionStart);
}

apikey ExternalMissionBindings::apiMissionStart(const std::string& name) {
    std::string path = std::string("data/scripts/missions/") + name + ".lua";

    Mission* mission = new Mission(path);
    World::instance()->player().addMission(mission);

    return mission->scriptKey();
}

