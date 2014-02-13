#pragma once

#include <list>
#include <string>


template<typename StateType> class Transition;

template<typename StateType>
class State {
public:
    State(State<StateType>* parent = nullptr);
    State(const std::string& name, State<StateType>* parent = nullptr);
    virtual ~State();

    const std::string& name() const;
    void setName(const std::string& name);

    State<StateType>* parentState();

    State<StateType>* initialSubstate();
    void setInitialSubstate(State<StateType>* initialSubstate);

    State<StateType>* terminationSubstate();
    void setTerminationSubstate(State<StateType>* terminationSubstate);

    State<StateType>* currentSubstate();
    void setCurrentSubstate(State<StateType>* substate);

    void makeCurrent();

    bool finished() const;

    std::list<State<StateType>*>& substates();
    void addSubstate(State<StateType>* state);
    void removeSubstate(State<StateType>* state);

    std::list<Transition<StateType>*>& transitions();
    void addTransition(Transition<StateType>* transition);
    void removeTransition(Transition<StateType>* transition);

    virtual void update(float deltaSec);

    virtual void start();

    virtual void onEntered();
    virtual void onLeft();


protected:
    std::string m_name;

    State<StateType>* m_parentState;
    std::list<State<StateType>*> m_substates;
    std::list<Transition<StateType>*> m_transitions;

    State<StateType>* m_initialSubstate;
    State<StateType>* m_terminationSubstate;
    State<StateType>* m_currentSubstate;
};

#include "state.inl"
