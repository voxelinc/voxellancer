#pragma once

#include <functional>

#include "eventpoll.h"

#include "utils/handle/handle.h"

class AiTask;

class AiTaskFinishedPoll : public EventPoll {
public:
    AiTaskFinishedPoll(AiTask* aitask, const std::shared_ptr<Callback>& callback);

protected:
    Handle<AiTask> m_aiTask;

    virtual bool poll() override;
    virtual bool isDead() override;

};

