#include "loopingtimer.h"

#include "glow/logging.h"

LoopingTimer::LoopingTimer(float interval, const std::shared_ptr<Callback>& callback):
    Timer(interval, callback)
{

}

