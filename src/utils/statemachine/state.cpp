#include "state.h"

#include <cassert>
#include <iostream>

#include <glow/logging.h>

#include "transition.h"


State::State(State* parentState):
    State("Unnamed state", parentState)
{

}

State::State(const std::string& name, State* parentState):
    m_name(name),
    m_parentState(parentState),
    m_initialSubState(nullptr),
    m_finalSubState(nullptr),
    m_currentSubState(nullptr)
{
    if (m_parentState) {
        m_parentState->addSubState(this);
    }
}

State::~State() {
    for (State* substate : m_subStates) {
        delete substate;
    }

    for (Transition* transition : m_transitions) {
        delete transition;
    }
}

const std::string& State::name() const {
    return m_name;
}

void State::setName(const std::string& name) {
    m_name = name;
}

State* State::parentState() {
    return m_parentState;
}

const State* State::parentState() const {
    return m_parentState;
}

State* State::initialSubState() {
    return m_initialSubState;
}

const State* State::initialSubState() const {
    return m_initialSubState;
}

void State::setInitialSubState(State* initialSubState) {
    m_initialSubState = initialSubState;
}

State* State::finalSubState() {
    return m_finalSubState;
}

const State* State::finalSubState() const {
    return m_finalSubState;
}

void State::setFinalSubState(State* finalSubState) {
    m_finalSubState = finalSubState;
}

State* State::currentSubState() {
    return m_currentSubState;
}

const State* State::currentSubState() const {
    return m_currentSubState;
}

void State::setCurrentSubState(State* currentSubState) {
    m_currentSubState = currentSubState;
}

bool State::finished() const {
    return m_finalSubState == m_currentSubState;
}

std::list<State*>& State::substates() {
    return m_subStates;
}

const std::list<State*>& State::substates() const {
    return m_subStates;
}

void State::addSubState(State* state) {
    m_subStates.push_back(state);

    if (!m_initialSubState) {
        m_initialSubState = state;
    }
}

void State::removeSubState(State* state) {
    assert(state->parentState() == this);

    if (m_initialSubState == state) {
        m_initialSubState = nullptr;
    }
    if (m_finalSubState == state) {
        m_finalSubState = nullptr;
    }

    m_subStates.remove(state);
    delete state;
}

std::list<Transition*>& State::transitions() {
    return m_transitions;
}

const std::list<Transition*>& State::transitions() const {
    return m_transitions;
}

void State::addTransition(Transition* transition) {
    assert(this == transition->from());
    m_transitions.push_back(transition);
}

void State::removeTransition(Transition* transition) {
    assert(transition->from() == this);

    m_transitions.remove(transition);
    delete transition;
}

void State::update(float deltaSec) {
    if (!m_currentSubState) {
        if (m_initialSubState) {
            m_currentSubState = m_initialSubState;
            m_currentSubState->onEntered();
		}
    }

    if (m_currentSubState) {
        for (Transition* transition : m_currentSubState->transitions()) {
            if (transition->isPossible()) {
                transit(transition->to());
                transition->onPerformed();
            }
        }
    }

    if (m_currentSubState) {
        m_currentSubState->update(deltaSec);
    }
}

State* State::pathToDescendant(State* descendant) {
    for(State* subState : m_subStates) {
        if (subState == descendant) {
            return this;
        }

        State* next = subState->pathToDescendant(descendant);
        if (next) {
            return subState;
        }
    }

    return nullptr;
}

void State::transit(State* target) {
    State* nextState = pathToDescendant(target);

    if (m_currentSubState && nextState != m_currentSubState) { // If the current substate is left
        m_currentSubState->leave();
    }

    if (nextState) { // Going down the tree or staying on the same level
        if (nextState == this) { // Stay on current level
            m_currentSubState = target;
            m_currentSubState->onEntered();
            return;
        } else { // Go one level deeper
            m_currentSubState = nextState;
            m_currentSubState->onEntered();
            m_currentSubState->transit(target);
        }
    } else { // Going up the tree
        m_currentSubState = nullptr;
        assert(m_parentState);
        m_parentState->transit(target);
    }
}

void State::onEntered() {
    glow::debug("ENTERING: %;", m_name);
}

void State::onLeft() {
    glow::debug("LEAVING: %;", m_name);
}

void State::leave() {
    if (m_currentSubState) {
        m_currentSubState->leave();
    }
    onLeft();
}

