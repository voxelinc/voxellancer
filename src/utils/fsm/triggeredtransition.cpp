#include "triggeredtransition.h"

TriggeredTransition::TriggeredTransition(State* from, State* to):
    Transition(from, to)
{
}

TriggeredTransition::TriggeredTransition(State* from, State* to, const std::string& name):
    Transition(from, to, name)
{
}

bool TriggeredTransition::possible() const {
    return m_triggered;
}

void TriggeredTransition::trigger() {
    m_triggered = true;
}
