#pragma once

#include <string>
#include <glm/glm.hpp>

#include "bindings.h"


class AiBindings : public Bindings {
public:
    AiBindings(GamePlayScript& script);


protected:
    virtual void bind() override;

    std::string apiGetFaction(apikey ship);
    int apiSetFaction(apikey ship, const std::string& faction);
    float apiGetFactionRelation(const std::string& factionA, const std::string& factionB);
    int apiSetFactionRelation(const std::string& factionA, const std::string& factionB, float friendliness);

    apikey apiOnAiTaskFinished(apikey aiTask, const std::string& callback);

    apikey apiCreateFlyToTask(apikey ship);
    int apiSetTargetPoint(apikey flyToTask, const glm::vec3& point);
    apikey apiCreateFightTask(apikey ship);
    int apiAddFightTaskTarget(apikey flyToTask, apikey worldObject);

    apikey apiTaskExecutor(apikey aiTask);
};

