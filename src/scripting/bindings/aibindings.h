#pragma once

#include "bindings.h"

class AiBindings : public Bindings {
public:
    AiBindings(GamePlayScript& script);

protected:
    virtual void initialize();

    apikey apiCreateFlyToTask(apikey ship);
    int apiSetTargetPoint(apikey flyToTask, float x, float y, float z);
};
