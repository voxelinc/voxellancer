#include "keytrigger.h"


KeyTrigger::KeyTrigger():
    KeyTrigger(-1)
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
        m_lastState = -1;
    }

    m_glfwKey = glfwKey;
}

void KeyTrigger::update(float deltaSec) {
    Trigger::update(deltaSec);

    if (m_glfwKey < 0) {
        return;
    }

    if (m_lastState < 0) {
        m_lastState = glfwGetKey(glfwGetCurrentContext(), m_glfwKey);
    } else {
        int currentState = glfwGetKey(glfwGetCurrentContext(), m_glfwKey);

        if (m_lastState == GLFW_RELEASE && currentState == GLFW_PRESS) {
            trigger();
        }
        m_lastState = currentState;
    }
}

