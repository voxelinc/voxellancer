#pragma once

#include <string>

#include "missions/mission.h"

#include "bindings.h"



/**
    API to manage missions from the outside
*/
class ExternalMissionBindings : public Bindings {
public:
    ExternalMissionBindings(GamePlayScript& script);


protected:
    virtual void bind() override;

    apikey apiMissionStart(const std::string& name);
    apikey apiOnMissionFailure(apikey missionKey, const std::string& callback);
    apikey apiOnMissionSuccess(apikey missionKey, const std::string& callback);

    apikey createStatePoll(apikey missionKey, MissionState state, const std::string& callback);
};

