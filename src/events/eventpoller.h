#pragma once

#include <list>
#include <memory>


class EventPoll;

class EventPoller {
public:
    EventPoller();
    ~EventPoller();

    void addPoll(std::shared_ptr<EventPoll> eventPoll);
    void removePoll(std::shared_ptr<EventPoll> eventPoll);

    void update(float deltaSec);


protected:
    std::list<std::shared_ptr<EventPoll>> m_eventPolls;
};

