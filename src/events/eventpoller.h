#pragma once

#include <list>
#include <memory>


class EventPoll;

class EventPoller {
public:
    EventPoller();
    ~EventPoller();

    void addPoll(EventPoll* eventPoll);
    void removePoll(EventPoll* eventPoll);

    void update(float deltaSec);


protected:
    std::list<std::unique_ptr<EventPoll>> m_eventPolls;
};

