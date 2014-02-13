#pragma once


class TriggeredTransition;

template<typename StateType>
class Trigger {
public:
    Trigger(TriggeredTransition<StateType>* transition = nullptr);

    TriggeredTransition<StateType>* transition();
    void setTransition(TriggeredTransition<StateType>* transition);

    void trigger();


protected:
    TriggeredTransition<StateType>* m_transition;
};

#include "trigger.inl"
