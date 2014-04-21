#pragma once

#include "ai/aigrouptask.h"


class SquadSeekTask : public AiGroupTask {
public:
    SquadSeekTask(Squad& squad, AiGroupTask* parent = nullptr);
    ~SquadSeekTask() override;

    void update(float deltaSec) override;


};

