#include "singleshottimer.h"


SingleShotTimer::SingleShotTimer(float interval, const std::shared_ptr<Callback>& callback):
    Timer(interval, callback),
    m_ticking(true)
{
}

bool SingleShotTimer::isDead() {
    return !m_ticking;
}

void SingleShotTimer::specialOnCallback() {
    Timer::specialOnCallback();
    m_ticking = false;
}

