#pragma once

#include <string>

#include "bindings.h"

class AiBindings : public Bindings {
public:
    AiBindings(GamePlayScript& script);

protected:
    virtual void initialize();

    std::string apiGetFactionName(apikey ship);
    float apiGetFactionRelation(const std::string& factionA, const std::string& factionB);
    int apiSetFactionRelation(const std::string& factionA, const std::string& factionB, float friendliness);


    apikey apiCreateFlyToTask(apikey ship);
    int apiSetTargetPoint(apikey flyToTask, float x, float y, float z);
};
