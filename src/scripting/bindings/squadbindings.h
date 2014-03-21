#pragma once

#include "bindings.h"


class SquadBindings : public Bindings {
public:
    SquadBindings(GamePlayScript& script);


protected:
    virtual void bind() override;

    apikey apiCreateSquad(apikey leader);
    int apiJoinSquad(apikey squad, apikey ship);

    int apiCreatePatrolWaypointsTask(apikey squad);
    int apiAddPatrolwWaypointPoint(apikey task, const glm::vec3& point);

    int apiCreateDefendAreaTask(apikey squad, const glm::vec3& point, float range);
    int apiAddDefendAreaPoint(apikey task, const glm::vec3& point);
};

