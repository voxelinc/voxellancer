#include "eventpoll.h"

EventPoll::EventPoll(const std::function<void()>& callback):
    m_callback(callback)
{

}

