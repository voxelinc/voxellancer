#include "actionkeymapping.h"


#ifdef WIN32
#include <windows.h>
#endif
#include <GL/glew.h>
#include <GLFW/glfw3.h>


ActionKeyMapping::ActionKeyMapping(std::string primary, std::string secondary, std::string name, bool toggleAction) :
    m_primaryMapping(primary),
    m_secondaryMapping(secondary),
    m_toggleAction(toggleAction),
    m_toggleStatus(false),
    m_name(name)
{
}

InputMapping ActionKeyMapping::mapping(InputClass inputClass) {
    if (inputClass == InputClass::Primary) {
        return m_primaryMapping;
    } else {
        return m_secondaryMapping;
    }
}

void ActionKeyMapping::setMapping(InputClass inputClass, InputMapping mapping) {
    if (inputClass == InputClass::Primary) {
        m_primaryMapping.set(mapping);
    } else {
        m_secondaryMapping.set(mapping);
    }
}

const std::string& ActionKeyMapping::name() {
    return m_name;
}

const std::string& ActionKeyMapping::mappingName(InputClass inputClass) {
    if (inputClass == InputClass::Primary) {
        return m_primaryMapping.name();
    } else {
        return m_secondaryMapping.name();
    }
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

SecondaryInputValues::SecondaryInputValues() {
    buttonCnt = 0;
    axisCnt = 0;
    buttonValues = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCnt);
    axisValues = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axisCnt);
}


