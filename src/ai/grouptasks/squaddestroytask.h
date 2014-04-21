#pragma once

#include "ai/aigrouptask.h"


class SquadDestroyTask : public AiGroupTask {
public:
    SquadDestroyTask(Squad& squad, AiGroupTask* parent = nullptr);
    ~SquadDestroyTask() override;

    void update(float deltaSec) override;
};

