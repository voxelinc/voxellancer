#include "singleshottimer.h"


SingleShotTimer::SingleShotTimer(float interval, const Callback& callback):
    Timer(interval, callback),
    m_fired(false)
{
}

bool SingleShotTimer::poll() {
    if (m_fired) {
        return false;
    } else {
        return Timer::poll();
    }
}

void SingleShotTimer::specialOnCallback() {
    Timer::specialOnCallback();
    m_fired = true;
    scheduleRemoval();
}

