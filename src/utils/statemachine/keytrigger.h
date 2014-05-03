#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "trigger.h"


/**
 * Triggers when the set key is pressed down after
 * the creation of this object
 */
class KeyTrigger : public Trigger {
public:
    KeyTrigger();
    KeyTrigger(int glfwKey);

    int key() const;
    void setKey(int glfwKey);

    virtual void update(float deltaSec) override;


protected:
    int m_glfwKey;
    int m_lastState;
};

