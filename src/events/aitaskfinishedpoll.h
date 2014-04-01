#pragma once

#include <functional>

#include "eventpoll.h"

#include "utils/handle/handle.h"

class AiTask;

class AiTaskFinishedPoll : public EventPoll {
public:
    AiTaskFinishedPoll(AiTask* aitask, const std::function<void()>& callback);

protected:
    Handle<AiTask> m_aiTask;

    virtual bool poll() override;
    virtual bool isDead() override;

};

