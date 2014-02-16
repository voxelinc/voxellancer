#include "timermanager.h"

TimerManager::TimerManager() {

}

TimerManager::~TimerManager() {

}

void TimerManager::registerTimer(Timer* timer) {
    m_timers.push_back(std::unique_ptr<Timer>(timer));
}

void TimerManager::update(float deltaSec) {
    for (std::list<std::unique_ptr<Timer>>::iterator i = m_timers.begin(); i != m_timers.end(); ++i) {
        Timer* timer = i->get();

        timer->update(deltaSec);
        if (!timer->ticking()) {
            i = m_timers.erase(i);
        }
    }
}

