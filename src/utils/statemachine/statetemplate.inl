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
    m_initialSubState(nullptr),
    m_finalSubState(nullptr),
    m_currentSubState(nullptr)
{
    if (m_parentState) {
        m_parentState->addSubState(m_self);
    }
}

template<typename StateType>
StateTemplate<StateType>::~StateTemplate() {
    for (StateType* substate : m_subStates) {
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
StateType* StateTemplate<StateType>::finalSubState() {
    return m_finalSubState;
}

template<typename StateType>
const StateType* StateTemplate<StateType>::finalSubState() const {
    return m_finalSubState;
}

template<typename StateType>
void StateTemplate<StateType>::setFinalSubState(StateType* finalSubState) {
    m_finalSubState = finalSubState;
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
StateType* StateTemplate<StateType>::pathToDescendant(StateType* descendant) {
    for(StateType* subState : m_subStates) {
        if (subState == descendant) {
            return subState;
        }

        StateType* next = subState->pathToDescendant(descendant);
        if (next) {
            return next;
        }
    }

    return nullptr;
}

template<typename StateType>
bool StateTemplate<StateType>::finished() const {
    return m_finalSubState == m_currentSubState;
}

template<typename StateType>
std::list<StateType*>& StateTemplate<StateType>::substates() {
    return m_subStates;
}

template<typename StateType>
const std::list<StateType*>& StateTemplate<StateType>::substates() const {
    return m_subStates;
}

template<typename StateType>
void StateTemplate<StateType>::addSubState(StateType* state) {
    m_subStates.push_back(state);
}

template<typename StateType>
void StateTemplate<StateType>::removeSubState(StateType* state) {
    assert(state->parentState() == m_self);

    m_subStates.remove(state);
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
            if (transition->isPossible()) {
                transit(transition->from(), transition->to());
                transition->onPerformed();
            }
        }
    } else {
    	if (m_initialSubState) {
            m_currentSubState = m_initialSubState;
            m_currentSubState->onEntered();
		}
    }

    if (m_currentSubState) {
        m_currentSubState->update(deltaSec);
    }
}

template<typename StateType>
void StateTemplate<StateType>::transit(StateType* position, StateType* target) {
    StateType* next = position->pathToDescendant(target);

    if(next) {
        m_currentSubState = next;
        m_currentSubState->onEntered();
    } else {
        m_currentSubState = nullptr;
        position->onLeft();
        next = position->parentState();
        assert(next);
    }

    if (next != target) {
        transit(next, target);
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

