#pragma once

#include <list>
#include <string>


template<typename StateType> class Transition;

/*
    This class is a template for State-classes inside a FiniteStateMachine.

    It s designed to be derived like: class ActualState: StateTemplate<ActualState> {...};
    This way you can nest states as you wish and still maintain the interface for the SubStates
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

    StateType* initialSubState();
    const StateType* initialSubState() const;
    void setInitialSubState(StateType* initialSubState);

    StateType* finalSubState();
    const StateType* finalSubState() const;
    void setFinalSubState(StateType* finalSubState);

    StateType* currentSubState();
    const StateType* currentSubState() const;
    void setCurrentSubState(StateType* substate);

    /*
        Returns direct child containing &descendant
        Returns nullptr if &descendant is no descendant of this
    */
    StateType* pathToDescendant(StateType* descendant);

    bool finished() const;

    std::list<StateType*>& substates();
    const std::list<StateType*>& substates() const;
    void addSubState(StateType* state);
    void removeSubState(StateType* state);

    std::list<Transition<StateType>*>& transitions();
    const std::list<Transition<StateType>*>& transitions() const;
    void addTransition(Transition<StateType>* transition);
    void removeTransition(Transition<StateType>* transition);

    /*
        Performs a Transition from the currentSubState, if such
        isPossible()
    */
    virtual void update(float deltaSec);

    /*
        Overrideable method that is called whenever a state or any of its substates come to be currentSubState
        This happens recursively up to the root-state
    */
    virtual void onEntered();

    /*
        Overrideable method that is called whenever a state ceases to be currentSubState
        This happens recursively up to the root-state
    */
    virtual void onLeft();


protected:
    std::string m_name;

    StateType* m_self;
    StateType* m_parentState;
    std::list<StateType*> m_subStates;
    std::list<Transition<StateType>*> m_transitions;

    StateType* m_initialSubState;
    StateType* m_finalSubState;
    StateType* m_currentSubState;


    void transit(StateType* position, StateType* target);
};

#include "statetemplate.inl"
