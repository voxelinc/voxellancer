#include "loopingtimer.h"

#include "glow/logging.h"

LoopingTimer::LoopingTimer(float interval, const std::function<void()>& callback):
    Timer(interval, callback)
{
    glow::debug("Created loopingtimeer %;", this);
}
