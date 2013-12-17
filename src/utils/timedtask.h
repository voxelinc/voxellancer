#pragma once

#include <chrono>


class TimedTask
{
public:
    TimedTask(std::chrono::duration<float> intervalSecs);
    virtual ~TimedTask();

    std::chrono::duration<float> intervalSecs() const;
    void setIntervalSecs(std::chrono::duration<float> intervalSecs);

    virtual bool isDue() const final;

    virtual void nudge() final;

    virtual void exec();


protected:
    std::chrono::duration<float> m_intervalSecs;
    std::chrono::high_resolution_clock::time_point m_lastExecution;
};

