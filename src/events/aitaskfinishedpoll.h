#pragma once

#include <functional>

#include "eventpoll.h"

#include "utils/handle/handle.h"

class AiTask;

class AiTaskFinishedPoll : public EventPoll {
public:
    AiTaskFinishedPoll(AiTask* aitask, const Callback& callback);


protected:
    Handle<AiTask> m_aiTask;
    bool m_fired;

    virtual bool poll() override;
    virtual void specialOnCallback() override;
};

