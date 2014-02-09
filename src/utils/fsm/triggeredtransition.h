#pragma once

#include "transition.h"


class TriggeredTransition: public Transition {
public:
    TriggeredTransition(State* from, State* to);
    TriggeredTransition(State* from, State* to, const std::string& name);

    virtual bool possible() const override;

    void trigger();


protected:
    bool m_triggered;
};

