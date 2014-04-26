#include "event.h"


Event::Event() = default;

Event::~Event() = default;

std::string Event::description() const {
    return eventName() + ": " + eventDescription();
}

std::string Event::eventName() const {
    return "Event";
}

std::string Event::eventDescription() const {
    return "No description";
}

