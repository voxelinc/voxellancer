#include "singleshottimer.h"


SingleShotTimer::SingleShotTimer(float interval, const std::function<void()>& callback):
    Timer(interval, callback),
    m_ticking(true)
{
}

bool SingleShotTimer::dead() const {
    return !m_ticking;
}

void SingleShotTimer::onCallbacked() {
    Timer::onCallbacked();
    m_ticking = false;
}

