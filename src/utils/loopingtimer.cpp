#include "loopingtimer.h"


LoopingTimer::LoopingTimer(float interval, const std::function<void()>& target):
    Timer(interval, target)
{
}

bool LoopingTimer::ticking() const {
    return true;
}
