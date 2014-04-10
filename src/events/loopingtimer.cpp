#include "loopingtimer.h"

#include "glow/logging.h"


LoopingTimer::LoopingTimer(float interval, const Callback& callback):
    Timer(interval, callback)
{

}

