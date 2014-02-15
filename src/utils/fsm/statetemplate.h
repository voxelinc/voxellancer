#pragma once

#include <list>
#include <string>


template<typename StateType> class Transition;

/*
    This class is a template for State-classes inside a FiniteStateMachine.

    It s designed to be derived like: class ActualState: StateTemplate<ActualState> {...};
    This way you can nest states as you wish and still maintain the interface for the Substates
    that you specify in ActualState (see GameState for a usage-example)
*/
template<typename StateType>
class StateTemplate {
public:
    StateTemplate(StateType* self, StateType* parent = nullptr);
    StateTemplate(const std::string& name, StateType* self, StateType* parent = nullptr);
    virtual ~StateTemplate();

    const std::string& name() const;
    void setName(const std::string& name);

    StateType* self();
    const StateType* self() const;

    StateType* parentState();
    const StateType* parentState() const;

    StateType* initialSubstate();
    const StateType* initialSubstate() const;
    void setInitialSubstate(StateType* initialSubstate);

    StateType* terminationSubstate();
    const StateType* terminationSubstate() const;
    void setTerminationSubstate(StateType* terminationSubstate);

    StateType* currentSubstate();
    const StateType* currentSubstate() const;
    void setCurrentSubstate(StateType* substate);

    /*
        Make this State the current substate of its parent, calling onEntered() on every state
        up to the root.
    */
    void makeCurrent();

    bool finished() const;

    std::list<StateType*>& substates();
    const std::list<StateType*>& substates() const;
    void addSubstate(StateType* state);
    void removeSubstate(StateType* state);

    std::list<Transition<StateType>*>& transitions();
    const std::list<Transition<StateType>*>& transitions() const;
    void addTransition(Transition<StateType>* transition);
    void removeTransition(Transition<StateType>* transition);

    /*
        Performs a Transition from the currentSubstate, if such is
        possible()
    */
    virtual void update(float deltaSec);

    /*
        Overrideable method that is called whenever a state or any of its substates become to be currentSubstate
        This happens recursively up to the root-state
    */
    virtual void onEntered();

    /*
        Overrideable method that is called whenever a state ceases to be currentSubstate
        This happens recursively up to the root-state
    */
    virtual void onLeft();


protected:
    std::string m_name;

    StateType* m_self;
    StateType* m_parentState;
    std::list<StateType*> m_substates;
    std::list<Transition<StateType>*> m_transitions;

    StateType* m_initialSubstate;
    StateType* m_terminationSubstate;
    StateType* m_currentSubstate;
};

#include "statetemplate.inl"
