#include "aitaskfinishedpoll.h"

#include "ai/aitask.h"


AiTaskFinishedPoll::AiTaskFinishedPoll(AiTask* aitask, const std::function<void()>& callback):
    EventPoll(callback),
    m_aiTask(aitask->handle())
{
}

bool AiTaskFinishedPoll::poll() {
    return m_aiTask.valid() ? m_aiTask->isFinished() : false;
}

bool AiTaskFinishedPoll::isDead() {
    return poll();
}

