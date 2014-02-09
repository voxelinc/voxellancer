#pragma once


class TriggeredTransition;

class Trigger {
public:
    Trigger(TriggeredTransition* transition = nullptr);

    TriggeredTransition* transition();
    void setTransition(TriggeredTransition* transition);

    void trigger();


protected:
    TriggeredTransition* m_transition;
};

