#include "timedtask.h"


TimedTask::TimedTask(std::chrono::duration<float> intervalSecs):
    m_intervalSecs(intervalSecs),
    m_lastExecution(std::chrono::high_resolution_clock::now())
{

}

TimedTask::~TimedTask() {

}

std::chrono::duration<float> TimedTask::intervalSecs() const {
    return m_intervalSecs;
}

void TimedTask::setIntervalSecs(std::chrono::duration<float> intervalSecs) {
    m_intervalSecs = intervalSecs;
}

bool TimedTask::isDue() const {
    return std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::high_resolution_clock::now() - m_lastExecution) >= m_intervalSecs;
}

void TimedTask::nudge() {
    if(isDue()) {
        m_lastExecution = std::chrono::high_resolution_clock::now();
        exec();
    }
}

void TimedTask::exec() {
    m_lastExecution = std::chrono::high_resolution_clock::now();
}
