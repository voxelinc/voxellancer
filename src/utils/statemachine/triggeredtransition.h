#pragma once

#include "transition.h"
#include "triggerable.h"


/*
    Transition that is invokable by calling trigger
    Useful for events like keypresses or reacting on an attack
*/
class TriggeredTransition: public Transition, public Triggerable {
public:
    TriggeredTransition(State* from, State* to);
    TriggeredTransition(State* from, State* to, const std::string& name);

    virtual bool isPossible() const override;

    virtual void trigger() override;

    virtual void onPerformed() override;


protected:
    bool m_triggered;
};
