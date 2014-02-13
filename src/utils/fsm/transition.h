#pragma once

#include <string>


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
