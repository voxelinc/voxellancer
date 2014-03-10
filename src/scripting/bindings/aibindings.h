#pragma once

#include "bindings.h"

class AiBindings : public Bindings {
public:
    AiBindings(GamePlayScript& script);

protected:
    virtual void initialize();

    int apiCreateFlyToTask(int key);
    int apiSetTargetPoint(int key, float x, float y, float z);
};
