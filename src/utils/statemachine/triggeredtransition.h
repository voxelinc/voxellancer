#pragma once

#include "transition.h"
#include "triggerable.h"


/*
    Transition that is invokable by calling trigger
    Useful for events like keypresses or reacting on an attack
*/
template<typename StateType>
class TriggeredTransition: public Transition<StateType>, public Triggerable {
public:
    TriggeredTransition(StateType* from, StateType* to);
    TriggeredTransition(StateType* from, StateType* to, const std::string& name);

    virtual bool isPossible() const override;

    virtual void trigger() override;

    virtual void onPerformed() override;


protected:
    bool m_triggered;
};

#include "triggeredtransition.inl"

