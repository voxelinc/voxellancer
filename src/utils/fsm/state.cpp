#include "state.h"

#include <cassert>
#include <iostream>

#include "transition.h"


State::State(State* parentState):
    State("Unnamed state", parentState)
{

}

State::State(const std::string& name, State* parentState):
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

State::~State() {
    for (State* substate : m_substates) {
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

State* State::initialSubstate() {
    return m_initialSubstate;
}

void State::setInitialSubstate(State* initialSubstate) {
    m_initialSubstate = initialSubstate;
}

State* State::terminationSubstate() {
    return m_terminationSubstate;
}

void State::setTerminationSubstate(State* terminationSubstate) {
    m_terminationSubstate = terminationSubstate;
}

State* State::currentSubstate() {
    return m_currentSubstate;
}

void State::setCurrentSubstate(State* currentSubstate) {
    m_currentSubstate = currentSubstate;
}

void State::makeCurrent() {
    if (m_parentState) {
        if (m_parentState->currentSubstate() != this) {
            m_parentState->setCurrentSubstate(this);
            m_parentState->makeCurrent();
            onEntered();
        }
    }
}

bool State::finished() const {
    return m_terminationSubstate == m_currentSubstate;
}

std::list<State*>& State::substates() {
    return m_substates;
}

void State::addSubstate(State* state) {
    m_substates.push_back(state);
}

void State::removeSubstate(State* state) {
    assert(state->parentState() == this);

    m_substates.remove(state);
    delete state;
}

std::list<Transition*>& State::transitions() {
    return m_transitions;
}

void State::addTransition(Transition* transition) {
    m_transitions.push_back(transition);
}

void State::removeTransition(Transition* transition) {
    assert(transition->from() == this);

    m_transitions.remove(transition);
    delete transition;
}

void State::update(float deltaSec) {
    if (m_currentSubstate) {
        for (Transition* transition : m_currentSubstate->transitions()) {
            if (transition->possible()) {
                m_currentSubstate->onLeft();
                m_currentSubstate = nullptr;
                transition->to()->makeCurrent();
            }
        }
        m_currentSubstate->update(deltaSec);
    }
}

void State::start() {
    onEntered();
    m_currentSubstate = m_initialSubstate;
    if (m_currentSubstate) {
        m_currentSubstate->onEntered();
    }
}

void State::onEntered() {
    std::cout << "ENTERING: " << m_name << std::endl;
}

void State::onLeft() {
    std::cout << "LEAVING: " << m_name << std::endl;
}

