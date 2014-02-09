#include "trigger.h"

#include "triggeredtransition.h"


Trigger::Trigger(TriggeredTransition* transition):
    m_transition(transition)
{
}

TriggeredTransition* Trigger::transition() {
    return m_transition;
}

void Trigger::setTransition(TriggeredTransition* transition) {
    m_transition = transition;
}

void Trigger::trigger() {
    if (m_transition) {
        m_transition->trigger();
    }
}
