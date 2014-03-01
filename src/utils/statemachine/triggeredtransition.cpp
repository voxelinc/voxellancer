#include "triggeredtransition.h"


TriggeredTransition::TriggeredTransition(State* from, State* to):
    TriggeredTransition(from, to, "Unnamed triggered transition")
{
}

TriggeredTransition::TriggeredTransition(State* from, State* to, const std::string& name):
    Transition(from, to, name),
    m_triggered(false)
{
}

bool TriggeredTransition::isPossible() const {
    return m_triggered;
}

void TriggeredTransition::trigger() {
    m_triggered = true;
}

void TriggeredTransition::onPerformed() {
    m_triggered = false;
}

