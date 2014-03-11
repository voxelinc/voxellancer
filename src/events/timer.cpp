#include "timer.h"

#include <cassert>
#include <iostream>
#include <algorithm>


Timer::Timer(float interval, const std::function<void()>& callback):
    EventPoll(callback),
    m_interval(interval),
    m_countdown(interval),
    m_scheduledCalls(0)
{
    assert(m_interval > 0.0f);
}

void Timer::update(float deltaSec) {
    EventPoll::update(deltaSec);

    m_countdown -= deltaSec;
    while (m_countdown < 0.0f) {
        m_scheduledCalls++;
        m_countdown += m_interval;
    }
}

bool Timer::poll() {
    return m_scheduledCalls > 0;
}

void Timer::specialOnCallback() {
    EventPoll::specialOnCallback();
    m_scheduledCalls--;
}

