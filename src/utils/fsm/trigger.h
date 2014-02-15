#pragma once


template<typename StateType> class TriggeredTransition;

/*
    Handle to a TriggeredTransition.
    The only advantage over holding (and trigger()ing) the transition directly is
    that a Trigger will just do nothing if no transition is registered.
*/
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
