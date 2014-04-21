#pragma once

#include "ai/aigrouptask.h"


class SquadSeekTask;
class SquadDestroyTask;

class RaidSectorTask: public AiGroupTask {
public:
    RaidSectorTask(Squad& squad, AiGroupTask* parent = nullptr);
    ~RaidSectorTask() override;

    void update(float deltaSec) override;


protected:
    std::unique_ptr<SquadSeekTask> m_seek;
    std::unique_ptr<SquadDestroyTask> m_destroy;
};

