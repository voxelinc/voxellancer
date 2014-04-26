#pragma once

#include "ai/aigrouptask.h"
#include "ai/basictasks/flytotask.h"


class SquadSeekTask : public AiGroupTask {
public:
    SquadSeekTask(Squad& squad, AiGroupTask* parent = nullptr);
    ~SquadSeekTask() override;

    void update(float deltaSec) override;


protected:
    std::shared_ptr<FlyToTask> m_leaderFlyTask;


    void onEntered() override;

    glm::vec3 newTargetPoint() const;
};

