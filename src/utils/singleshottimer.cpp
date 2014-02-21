#include "singleshottimer.h"


SingleShotTimer::SingleShotTimer(float interval, const std::function<void()>& target):
    Timer(interval, target),
    m_ticking(true)
{
}

bool SingleShotTimer::ticking() const {
    return m_ticking;
}

void SingleShotTimer::onFired() {
    m_ticking = false;
}
