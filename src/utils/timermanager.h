/*#pragma once

#include <memory>
#include <list>

#include "timer.h"


    Class for registering timers an updating them all together

    Non-ticking timers are removed
class TimerManager {
public:
    TimerManager();
    ~TimerManager();

        Timer ownership goes to the TimerManager
    void registerTimer(Timer* timer);

    void update(float deltaSec);


protected:
    std::list<std::unique_ptr<Timer>> m_timers;
};

    */
