#include "loopingtimer.h"

#include <iostream>

LoopingTimer::LoopingTimer(float interval, const std::function<void()>& callback):
    Timer(interval, callback)
{
    std::cout << "Created loopingtimeer "<<this << std::endl;
}
