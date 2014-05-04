#include "aitaskfinishedpoll.h"

#include "ai/aitask.h"


AiTaskFinishedPoll::AiTaskFinishedPoll(AiTask* aitask, const Callback& callback):
    EventPoll(callback),
    m_aiTask(makeHandle(aitask))
{
}

bool AiTaskFinishedPoll::poll() {
    return m_aiTask.valid() ? m_aiTask->isFinished() : false;
}

bool AiTaskFinishedPoll::isDead() {
    return poll();
}

