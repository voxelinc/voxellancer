#pragma once


template<typename StateType>
TriggeredTransition<StateType>::TriggeredTransition(StateType* from, StateType* to):
    TriggeredTransition(from, to, "Unnamed triggered transition")
{
}

template<typename StateType>
TriggeredTransition<StateType>::TriggeredTransition(StateType* from, StateType* to, const std::string& name):
    Transition<StateType>(from, to, name),
    m_triggered(false)
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

template<typename StateType>
void TriggeredTransition<StateType>::onPerformed() {
    m_triggered = false;
}
