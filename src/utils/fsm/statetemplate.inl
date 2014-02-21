#pragma once

#include <cassert>

#include <glow/logging.h>

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
    m_initialSubstate(nullptr),
    m_terminationSubstate(nullptr),
    m_currentSubstate(nullptr)
{
    if (m_parentState) {
        m_parentState->addSubstate(m_self);
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
StateType* StateTemplate<StateType>::initialSubstate() {
    return m_initialSubstate;
}

template<typename StateType>
const StateType* StateTemplate<StateType>::initialSubstate() const {
    return m_initialSubstate;
}

template<typename StateType>
void StateTemplate<StateType>::setInitialSubstate(StateType* initialSubstate) {
    m_initialSubstate = initialSubstate;
}

template<typename StateType>
StateType* StateTemplate<StateType>::terminationSubstate() {
    return m_terminationSubstate;
}

template<typename StateType>
const StateType* StateTemplate<StateType>::terminationSubstate() const {
    return m_terminationSubstate;
}

template<typename StateType>
void StateTemplate<StateType>::setTerminationSubstate(StateType* terminationSubstate) {
    m_terminationSubstate = terminationSubstate;
}

template<typename StateType>
StateType* StateTemplate<StateType>::currentSubstate() {
    return m_currentSubstate;
}

template<typename StateType>
const StateType* StateTemplate<StateType>::currentSubstate() const {
    return m_currentSubstate;
}

template<typename StateType>
void StateTemplate<StateType>::setCurrentSubstate(StateType* currentSubstate) {
    m_currentSubstate = currentSubstate;
}

template<typename StateType>
void StateTemplate<StateType>::makeCurrent() {
    if (m_parentState) {
        if (m_parentState->currentSubstate() != m_self) {
            m_parentState->setCurrentSubstate(m_self);
            m_parentState->makeCurrent();
            onEntered();
        }
    }
}

template<typename StateType>
bool StateTemplate<StateType>::finished() const {
    return m_terminationSubstate == m_currentSubstate;
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
void StateTemplate<StateType>::addSubstate(StateType* state) {
    m_substates.push_back(state);
}

template<typename StateType>
void StateTemplate<StateType>::removeSubstate(StateType* state) {
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
    if (m_currentSubstate) {
        for (Transition<StateType>* transition : m_currentSubstate->transitions()) {
            if (transition->possible()) {
                m_currentSubstate->onLeft();
                m_currentSubstate = nullptr;
                transition->to()->makeCurrent();

                transition->onPerformed();
            }
        }
    } else {
    	if (m_initialSubstate) {
			m_initialSubstate->makeCurrent();
		}
    }

    if (m_currentSubstate) {
        m_currentSubstate->update(deltaSec);
    }
}

template<typename StateType>
void StateTemplate<StateType>::onEntered() {
    glow::debug("ENTERING: %;", m_name);
}

template<typename StateType>
void StateTemplate<StateType>::onLeft() {
    glow::debug("LEAVING: %;", m_name);
}

