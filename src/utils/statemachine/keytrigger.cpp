#include "keytrigger.h"


KeyTrigger::KeyTrigger():
    KeyTrigger(GLFW_KEY_UNKNOWN)
{

}

KeyTrigger::KeyTrigger(int glfwKey):
    m_glfwKey(glfwKey),
    m_lastState(GLFW_PRESS)
{

}

int KeyTrigger::key() const {
    return m_glfwKey;
}

void KeyTrigger::setKey(int glfwKey) {
    if (m_glfwKey != glfwKey) {
        m_lastState = GLFW_PRESS;
    }

    m_glfwKey = glfwKey;
}

void KeyTrigger::update(float deltaSec) {
    Trigger::update(deltaSec);

    int currentState = glfwGetKey(glfwGetCurrentContext(), m_glfwKey);

    if (m_lastState == GLFW_RELEASE && currentState == GLFW_PRESS) {
        trigger();
    }
    m_lastState = currentState;
}

