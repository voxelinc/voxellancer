#pragma once

#include <list>
#include <string>


class Transition;

/**
 * Abstract State that can function as a StateMachine
 * This way you can nest states as you wish and still maintain the interface for the SubStates
 * that you specify in ActualState (see GameState for a usage-example)
 */
class State {
public:
    State(State* parent = nullptr);
    State(const std::string& name, State* parent = nullptr);
    virtual ~State();

    const std::string& name() const;
    void setName(const std::string& name);

    State* parentState();
    const State* parentState() const;

    State* initialSubState();
    const State* initialSubState() const;
    void setInitialSubState(State* initialSubState);

    State* finalSubState();
    const State* finalSubState() const;
    void setFinalSubState(State* finalSubState);

    State* currentSubState();
    const State* currentSubState() const;
    void setCurrentSubState(State* substate);

    bool finished() const;

    std::list<State*>& substates();
    const std::list<State*>& substates() const;
    void addSubState(State* state);
    void removeSubState(State* state);

    std::list<Transition*>& transitions();
    const std::list<Transition*>& transitions() const;
    void addTransition(Transition* transition);
    void removeTransition(Transition* transition);

    /**
     * Performs a Transition from the currentSubState, if such
     * isPossible()
     */
    virtual void update(float deltaSec);

    /**
     * Overrideable method that is called whenever a state or any of its substates come to be currentSubState
     * This happens recursively up to the root-state
     */
    virtual void onEntered();

    /**
     * Overrideable method that is called whenever a state ceases to be currentSubState
     * This happens recursively up to the root-state
     */
    virtual void onLeft();


protected:
    std::string m_name;

    State* m_parentState;
    std::list<State*> m_subStates;
    std::list<Transition*> m_transitions;

    State* m_initialSubState;
    State* m_finalSubState;
    State* m_currentSubState;


    /**
     * Returns direct substate having &descendant as a descendant
     * Returns m_self if  descendant is substate of this
     * Returns nullptr if &descendant is no descendant of  this
     */
    State* pathToDescendant(State* descendant);

    /**
     * Ensures the graph of m_currentSubState points from the root to targt
     * calls onLeft() on every state left and onEntered() on every entered
     */
    void transit(State* target);

    void leave();
};

