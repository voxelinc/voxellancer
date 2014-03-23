#include "externalmissionbindings.h"

#include "events/eventpoller.h"
#include "events/missionstatepoll.h"

#include "scripting/gameplayscript.h"
#include "scripting/elematelua/luawrapper.h"

#include "world/world.h"

#include "player.h"


ExternalMissionBindings::ExternalMissionBindings(GamePlayScript& script):
    Bindings(script)
{

}

void ExternalMissionBindings::bind() {
    m_lua.Register("missionStart", this, &ExternalMissionBindings::apiMissionStart);
    m_lua.Register("onMissionSuccess", this, &ExternalMissionBindings::apiOnMissionSuccess);
    m_lua.Register("onMissionFailure", this, &ExternalMissionBindings::apiOnMissionFailure);
}

apikey ExternalMissionBindings::apiMissionStart(const std::string& name) {
    std::string path = std::string("data/scripts/missions/") + name + ".lua";

    Mission* mission = new Mission(path);
    World::instance()->player().addMission(mission);

    return mission->scriptKey();
}

apikey ExternalMissionBindings::apiOnMissionFailure(apikey missionKey, const std::string& callback) {
    return createStatePoll(missionKey, MissionState::Failed, callback);
}

apikey ExternalMissionBindings::apiOnMissionSuccess(apikey missionKey, const std::string& callback) {
    return createStatePoll(missionKey, MissionState::Succeeded, callback);
}

apikey ExternalMissionBindings::createStatePoll(apikey missionKey, MissionState state, const std::string& callback) {
    Mission* mission = m_scriptEngine.get<Mission>(missionKey);
    if (!mission) {
       return -1;
    }

    MissionStatePoll* poll = new MissionStatePoll(mission->handle(), state, [=] { m_lua.call(callback, missionKey); });
    World::instance()->eventPoller().addPoll(poll);
    m_script.addLocal(poll->scriptKey());

    return poll->scriptKey();
}

