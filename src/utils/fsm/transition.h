#pragma once

#include <string>


class State;

class Transition {
public:
    Transition(State* from, State* to);
    Transition(State* from, State* to, const std::string& name);
    virtual ~Transition();

    const std::string& name() const;
    void setName(const std::string& name);

    State* from();
    State* to();

    virtual bool possible() const = 0;

    virtual void onPerformed();


protected:
    State* m_from;
    State* m_to;
    std::string m_name;
};

