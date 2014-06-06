#include "introinput.h"

#include <GLFW/glfw3.h>

#include <glow/logging.h>

#include "utils/statemachine/trigger.h"

#include "intro.h"


IntroInput::IntroInput(Intro& intro):
    m_intro(intro)
{
}

IntroInput::~IntroInput() = default;

void IntroInput::onKeyEvent(int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        m_intro.overTrigger().trigger();
    }
}

