#include "eventpoller.h"

#include "eventpoll.h"

#include "scripting/scriptengine.h"

#include "world/world.h"


EventPoller::EventPoller()
{

}

EventPoller::~EventPoller() = default;

void EventPoller::addPoll(std::shared_ptr<EventPoll> eventPoll) {
    m_eventPolls[eventPoll.get()] = eventPoll;
    World::instance()->scriptEngine().registerScriptable(eventPoll.get());
}

void EventPoller::removePoll(EventPoll* eventPoll) {
    World::instance()->scriptEngine().unregisterScriptable(eventPoll);
    m_eventPolls.erase(eventPoll);
}

void EventPoller::update(float deltaSec) {
    for (auto iter = m_eventPolls.begin(); iter != m_eventPolls.end();) {
        EventPoll* poll = iter->second.get();
        poll->update(deltaSec);
        if (poll->isDead()) {
            iter = m_eventPolls.erase(iter);
        } else {
            ++iter;
        }
    }
}
