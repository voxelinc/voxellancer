#pragma once

#include "transition.h"


template<typename StateType>
class TriggeredTransition: public Transition<StateType> {
public:
    TriggeredTransition(State<StateType>* from, State<StateType>* to);
    TriggeredTransition(State<StateType>* from, State<StateType>* to, const std::string& name);

    virtual bool possible() const override;

    void trigger();


protected:
    bool m_triggered;
};

#include "triggeredtransition.h"

