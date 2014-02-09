#pragma once

#include <list>
#include <string>


class Transition;

class State {
public:
    State(State* parent = nullptr);
    State(const std::string& name, State* parent = nullptr);
    virtual ~State();

    const std::string& name() const;
    void setName(const std::string& name);

    State* parentState();

    State* initialSubstate();
    void setInitialSubstate(State* initialSubstate);

    State* terminationSubstate();
    void setTerminationSubstate(State* terminationSubstate);

    State* currentSubstate();
    void setCurrentSubstate(State* substate);

    void makeCurrent();

    bool finished() const;

    std::list<State*>& substates();
    void addSubstate(State* state);
    void removeSubstate(State* state);

    std::list<Transition*>& transitions();
    void addTransition(Transition* transition);
    void removeTransition(Transition* transition);

    virtual void update(float deltaSec);

    virtual void start();

    virtual void onEntered();
    virtual void onLeft();


protected:
    std::string m_name;

    State* m_parentState;
    std::list<State*> m_substates;
    std::list<Transition*> m_transitions;

    State* m_initialSubstate;
    State* m_terminationSubstate;
    State* m_currentSubstate;
};

