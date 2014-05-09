#include "aitaskfinishedpoll.h"

#include "ai/aitask.h"


AiTaskFinishedPoll::AiTaskFinishedPoll(AiTask* aitask, const Callback& callback):
    EventPoll(callback),
    m_aiTask(makeHandle(aitask)),
    m_fired(false)
{
}

bool AiTaskFinishedPoll::poll() {
    if (m_aiTask.valid()) {
        return m_aiTask->isFinished() && !m_fired;
    } else {
        return false;
    }
}

void AiTaskFinishedPoll::specialOnCallback() {
    EventPoll::specialOnCallback();
    m_fired = true;
    kill();
}

