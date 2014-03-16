#pragma once

#include <functional>

#include "eventpoll.h"


class Timer: public EventPoll {
public:
    Timer(float interval, const std::function<void()>& callback);

    virtual void update(float deltaSec) override;


protected:
    float m_interval;
    float m_countdown;
    int m_scheduledCalls;

    virtual bool poll() override;
    virtual void specialOnCallback() override;
};

