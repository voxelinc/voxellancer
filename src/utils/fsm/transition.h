#pragma once

#include <string>


/*
    Abstract base class for a transition from one state to another. Derived
    classes need to implement possible().
    Transitions register themself at from. to isn't informed it's "target" of a transition.
    Note that Transitions can go from any State to any other State, no matter which
    State they are nested in.
*/
template<typename StateType>
class Transition {
public:
    Transition(StateType* from, StateType* to);
    Transition(StateType* from, StateType* to, const std::string& name);
    virtual ~Transition();

    const std::string& name() const;
    void setName(const std::string& name);

    StateType* from();
    StateType* to();

    virtual bool possible() const = 0;

    virtual void onPerformed();


protected:
    StateType* m_from;
    StateType* m_to;
    std::string m_name;
};

#include "transition.inl"
