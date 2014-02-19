#pragma once

#include <cassert>
#include <iostream>

#include "transition.h"

template<typename StateType>
StateTemplate<StateType>::StateTemplate(StateType* self, StateType* parentState):
    StateTemplate("Unnamed state", self, parentState)
{

}

template<typename StateType>
StateTemplate<StateType>::StateTemplate(const std::string& name, StateType* self, StateType* parentState):
    m_name(name),
    m_self(self),
    m_parentState(parentState),
    m_initialSubState(nullptr),
    m_terminationSubState(nullptr),
    m_currentSubState(nullptr)
{
    if (m_parentState) {
        m_parentState->addSubState(m_self);
    }
}

template<typename StateType>
StateTemplate<StateType>::~StateTemplate() {
    for (StateType* substate : m_substates) {
        delete substate;
    }

    for (Transition<StateType>* transition : m_transitions) {
        delete transition;
    }
}

template<typename StateType>
const std::string& StateTemplate<StateType>::name() const {
    return m_name;
}

template<typename StateType>
void StateTemplate<StateType>::setName(const std::string& name) {
    m_name = name;
}

template<typename StateType>
StateType* StateTemplate<StateType>::self() {
    return m_self;
}

template<typename StateType>
const StateType* StateTemplate<StateType>::self() const {
    return m_self;
}

template<typename StateType>
StateType* StateTemplate<StateType>::parentState() {
    return m_parentState;
}

template<typename StateType>
const StateType* StateTemplate<StateType>::parentState() const {
    return m_parentState;
}

template<typename StateType>
StateType* StateTemplate<StateType>::initialSubState() {
    return m_initialSubState;
}

template<typename StateType>
const StateType* StateTemplate<StateType>::initialSubState() const {
    return m_initialSubState;
}

template<typename StateType>
void StateTemplate<StateType>::setInitialSubState(StateType* initialSubState) {
    m_initialSubState = initialSubState;
}

template<typename StateType>
StateType* StateTemplate<StateType>::terminationSubState() {
    return m_terminationSubState;
}

template<typename StateType>
const StateType* StateTemplate<StateType>::terminationSubState() const {
    return m_terminationSubState;
}

template<typename StateType>
void StateTemplate<StateType>::setTerminationSubState(StateType* terminationSubState) {
    m_terminationSubState = terminationSubState;
}

template<typename StateType>
StateType* StateTemplate<StateType>::currentSubState() {
    return m_currentSubState;
}

template<typename StateType>
const StateType* StateTemplate<StateType>::currentSubState() const {
    return m_currentSubState;
}

template<typename StateType>
void StateTemplate<StateType>::setCurrentSubState(StateType* currentSubState) {
    m_currentSubState = currentSubState;
}

template<typename StateType>
void StateTemplate<StateType>::makeCurrent() {
    if (m_parentState) {
        if (m_parentState->currentSubState() != m_self) {
            m_parentState->setCurrentSubState(m_self);
            m_parentState->makeCurrent();
            onEntered();
        }
    }
}

template<typename StateType>
bool StateTemplate<StateType>::finished() const {
    return m_terminationSubState == m_currentSubState;
}

template<typename StateType>
std::list<StateType*>& StateTemplate<StateType>::substates() {
    return m_substates;
}

template<typename StateType>
const std::list<StateType*>& StateTemplate<StateType>::substates() const {
    return m_substates;
}

template<typename StateType>
void StateTemplate<StateType>::addSubState(StateType* state) {
    m_substates.push_back(state);
}

template<typename StateType>
void StateTemplate<StateType>::removeSubState(StateType* state) {
    assert(state->parentState() == m_self);

    m_substates.remove(state);
    delete state;
}

template<typename StateType>
std::list<Transition<StateType>*>& StateTemplate<StateType>::transitions() {
    return m_transitions;
}

template<typename StateType>
const std::list<Transition<StateType>*>& StateTemplate<StateType>::transitions() const {
    return m_transitions;
}

template<typename StateType>
void StateTemplate<StateType>::addTransition(Transition<StateType>* transition) {
    m_transitions.push_back(transition);
}

template<typename StateType>
void StateTemplate<StateType>::removeTransition(Transition<StateType>* transition) {
    assert(transition->from() == m_self);

    m_transitions.remove(transition);
    delete transition;
}

template<typename StateType>
void StateTemplate<StateType>::update(float deltaSec) {
    if (m_currentSubState) {
        for (Transition<StateType>* transition : m_currentSubState->transitions()) {
            if (transition->possible()) {
                m_currentSubState->onLeft();
                m_currentSubState = nullptr;
                transition->to()->makeCurrent();

                transition->onPerformed();
            }
        }
    } else {
    	if (m_initialSubState) {
			m_initialSubState->makeCurrent();
		}
    }

    if (m_currentSubState) {
        m_currentSubState->update(deltaSec);
    }
}

template<typename StateType>
void StateTemplate<StateType>::onEntered() {
    std::cout << "ENTERING: " << m_name << std::endl;
}

template<typename StateType>
void StateTemplate<StateType>::onLeft() {
    std::cout << "LEAVING: " << m_name << std::endl;
}

