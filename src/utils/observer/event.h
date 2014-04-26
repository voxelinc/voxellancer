#pragma once

#include <string>


class Event {
public:
    Event();
    virtual ~Event();

    std::string description() const;


protected:
    virtual std::string eventName() const;
    virtual std::string eventDescription() const;
};
