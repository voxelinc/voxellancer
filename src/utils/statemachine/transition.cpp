#include "transition.h"

#include <assert.h>

#include "state.h"


Transition::Transition(State* from, State* to):
    Transition(from, to, "Unnamed transition")
{
}

Transition::Transition(State* from, State* to, const std::string& name):
    m_from(from),
    m_to(to),
    m_name(name)
{
    m_from->addTransition(this);
}

Transition::~Transition() {

}

const std::string& Transition::name() const {
    return m_name;
}

void Transition::setName(const std::string& name) {
    m_name = name;
}

State* Transition::from() {
    return m_from;
}

State* Transition::to() {
    return m_to;
}

void Transition::onPerformed() {

}

