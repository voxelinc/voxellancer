#pragma once


template<typename StateType>
TriggeredTransition<StateType>::TriggeredTransition(State<StateType>* from, State<StateType>* to):
    Transition(from, to)
{
}

template<typename StateType>
TriggeredTransition<StateType>::TriggeredTransition(State<StateType>* from, State<StateType>* to, const std::string& name):
    Transition(from, to, name)
{
}

template<typename StateType>
bool TriggeredTransition<StateType>::possible() const {
    return m_triggered;
}

template<typename StateType>
void TriggeredTransition<StateType>::trigger() {
    m_triggered = true;
}

