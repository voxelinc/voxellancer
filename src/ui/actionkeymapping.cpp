#include "actionkeymapping.h"

ActionKeyMapping::ActionKeyMapping(char* primary, char* secondary, std::string name) :
m_primaryMapping(primary),
m_secondaryMapping(secondary),
m_toggleAction(false),
m_toggleStatus(false),
m_name(name) {
}

ActionKeyMapping::ActionKeyMapping(char* primary, char* secondary, std::string name, bool toggleAction) :
m_primaryMapping(primary),
m_secondaryMapping(secondary),
m_toggleAction(toggleAction),
m_toggleStatus(false),
m_name(name) {
}

InputMapping ActionKeyMapping::mapping(bool primary) {
    if (primary) {
        return m_primaryMapping;
    } else {
        return m_secondaryMapping;
    }
}

void ActionKeyMapping::setMapping(InputMapping mapping, bool primary) {
    if (primary) {
        m_primaryMapping.set(mapping);
    } else {
        m_secondaryMapping.set(mapping);
    }
}

std::string ActionKeyMapping::name() {
    return m_name;
}

bool ActionKeyMapping::toggleAction() {
    return m_toggleAction;
}

bool ActionKeyMapping::toggleStatus() {
    return m_toggleStatus;
}

void ActionKeyMapping::setToggleStatus(bool status) {
    m_toggleStatus = status;
}