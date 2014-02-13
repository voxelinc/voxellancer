#pragma once

#include <cassert>
#include <iostream>

#include "transition.h"

template<typename StateType>
State<StateType>::State(State<StateType>* parentState):
    State("Unnamed state", parentState)
{

}

template<typename StateType>
State<StateType>::State(const std::string& name, State<StateType>* parentState):
    m_name(name),
    m_parentState(parentState),
    m_initialSubstate(nullptr),
    m_terminationSubstate(nullptr),
    m_currentSubstate(nullptr)
{
    if (m_parentState) {
        m_parentState->addSubstate(this);
    }
}

template<typename StateType>
State<StateType>::~State() {
    for (State<StateType>* substate : m_substates) {
        delete substate;
    }

    for (Transition<StateType>* transition : m_transitions) {
        delete transition;
    }
}

template<typename StateType>
const std::string& State<StateType>::name() const {
    return m_name;
}

template<typename StateType>
void State<StateType>::setName(const std::string& name) {
    m_name = name;
}

template<typename StateType>
State<StateType>* State<StateType>::parentState() {
    return m_parentState;
}

template<typename StateType>
State<StateType>* State<StateType>::initialSubstate() {
    return m_initialSubstate;
}

template<typename StateType>
void State<StateType>::setInitialSubstate(State<StateType>* initialSubstate) {
    m_initialSubstate = initialSubstate;
}

template<typename StateType>
State<StateType>* State<StateType>::terminationSubstate() {
    return m_terminationSubstate;
}

template<typename StateType>
void State<StateType>::setTerminationSubstate(State<StateType>* terminationSubstate) {
    m_terminationSubstate = terminationSubstate;
}

template<typename StateType>
State<StateType>* State<StateType>::currentSubstate() {
    return m_currentSubstate;
}

template<typename StateType>
void State<StateType>::setCurrentSubstate(State<StateType>* currentSubstate) {
    m_currentSubstate = currentSubstate;
}

template<typename StateType>
void State<StateType>::makeCurrent() {
    if (m_parentState) {
        if (m_parentState->currentSubstate() != this) {
            m_parentState->setCurrentSubstate(this);
            m_parentState->makeCurrent();
            onEntered();
        }
    }
}

template<typename StateType>
bool State<StateType>::finished() const {
    return m_terminationSubstate == m_currentSubstate;
}

template<typename StateType>
std::list<State<StateType>*>& State<StateType>::substates() {
    return m_substates;
}

template<typename StateType>
void State<StateType>::addSubstate(State<StateType>* state) {
    m_substates.push_back(state);
}

template<typename StateType>
void State<StateType>::removeSubstate(State<StateType>* state) {
    assert(state->parentState() == this);

    m_substates.remove(state);
    delete state;
}

template<typename StateType>
std::list<Transition<StateType>*>& State<StateType>::transitions() {
    return m_transitions;
}

template<typename StateType>
void State<StateType>::addTransition(Transition<StateType>* transition) {
    m_transitions.push_back(transition);
}

template<typename StateType>
void State<StateType>::removeTransition(Transition<StateType>* transition) {
    assert(transition->from() == this);

    m_transitions.remove(transition);
    delete transition;
}

template<typename StateType>
void State<StateType>::update(float deltaSec) {
    if (m_currentSubstate) {
        for (Transition<StateType>* transition : m_currentSubstate->transitions()) {
            if (transition->possible()) {
                m_currentSubstate->onLeft();
                m_currentSubstate = nullptr;
                transition->to()->makeCurrent();
            }
        }
        m_currentSubstate->update(deltaSec);
    }
}

template<typename StateType>
void State<StateType>::start() {
    onEntered();
    m_currentSubstate = m_initialSubstate;
    if (m_currentSubstate) {
        m_currentSubstate->onEntered();
    }
}

template<typename StateType>
void State<StateType>::onEntered() {
    std::cout << "ENTERING: " << m_name << std::endl;
}

template<typename StateType>
void State<StateType>::onLeft() {
    std::cout << "LEAVING: " << m_name << std::endl;
}

