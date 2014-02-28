#pragma once


class Triggerable;

/*
    Handle to a TriggeredTransition.
    The only advantage over holding (and trigger()ing) the transition directly is
    that a Trigger will just do nothing if no transition is registered.
*/
class Trigger {
public:
    Trigger(Triggerable* target = nullptr);

    Triggerable* target();
    void setTarget(Triggerable* target);

    void trigger();

    virtual void update(float deltaSec);


protected:
    Triggerable* m_target;
};

