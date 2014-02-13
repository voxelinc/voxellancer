#include "trigger.h"

#include "triggeredtransition.h"


template<typename StateType>
Trigger<StateType>::Trigger(TriggeredTransition<StateType>* transition):
    m_transition(transition)
{
}

template<typename StateType>
TriggeredTransition* Trigger<StateType>::transition() {
    return m_transition;
}

template<typename StateType>
void Trigger<StateType>::setTransition(TriggeredTransition<StateType>* transition) {
    m_transition = transition;
}

template<typename StateType>
void Trigger<StateType>::trigger() {
    if (m_transition) {
        m_transition->trigger();
    }
}

