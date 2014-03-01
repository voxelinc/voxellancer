#pragma once

#include <string>


class State;

/*
    Abstract base class for a transition from one state to another. Derived
    classes need to implement isPossible(). The actual transition is performed by the update() of
    the parentstate of from-
    Transitions register themself at from, no need to call addTransition() on the State. to isn't informed it's "target" of a transition.
    Note that Transitions can go from any State to any other State, no matter which State they are nested in.
*/
class Transition {
public:
    Transition(State* from, State* to);
    Transition(State* from, State* to, const std::string& name);
    virtual ~Transition();

    const std::string& name() const;
    void setName(const std::string& name);

    State* from();
    State* to();

    virtual bool isPossible() const = 0;

    virtual void onPerformed();


protected:
    State* m_from;
    State* m_to;
    std::string m_name;
};

