#include "timer.h"

#include <cassert>
#include <algorithm>


Timer::Timer(float interval, const std::function<void()>& target):
    m_interval(interval),
    m_countdown(interval),
    m_target(target)
{
    assert(m_interval > 0.0f);
}

void Timer::update(float deltaSec) {
    m_countdown -= deltaSec;
    while (m_countdown < 0.0f) {
        m_target();
        onFired();
        m_countdown += m_interval;
    }
}

void Timer::onFired() {

}

