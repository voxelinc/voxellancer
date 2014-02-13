#pragma once

#include "state.h"


template<typename StateType>
Transition<StateType>::Transition(StateType* from, StateType* to):
    m_from(from),
    m_to(to),
    m_name("Unnamed transition")
{
}

template<typename StateType>
Transition<StateType>::Transition(StateType* from, StateType* to, const std::string& name):
    m_from(from),
    m_to(to),
    m_name(name)
{
}

template<typename StateType>
Transition<StateType>::~Transition() {

}

template<typename StateType>
const std::string& Transition<StateType>::name() const {
    return m_name;
}

template<typename StateType>
void Transition<StateType>::setName(const std::string& name) {
    m_name = name;
}

template<typename StateType>
StateType* Transition<StateType>::from() {
    return m_from;
}

template<typename StateType>
StateType* Transition<StateType>::to() {
    return m_to;
}

template<typename StateType>
void Transition<StateType>::onPerformed() {

}

