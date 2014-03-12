#pragma once

#include "bindings.h"

class SquadBindings : public Bindings {
public:
    SquadBindings(GamePlayScript& script);

protected:
    virtual void initialize();

    apikey apiCreateSquad(apikey leader);
    int apiCreatePatrolWaypointsTask(apikey squad);
    int apiAddPatrolwWaypointPoint(apikey task, const glm::vec3& point);
    int apiJoinSquad(apikey squad, apikey ship);

};
