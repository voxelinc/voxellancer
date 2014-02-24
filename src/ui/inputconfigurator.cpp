#include "inputconfigurator.h"


#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glow/logging.hpp>

#include "ui/hud/hud.h"
#include "inputhandler.h"


InputConfigurator::InputConfigurator(std::vector<ActionKeyMapping*>* actions, SecondaryInputValues *secondaryInputValues, Property<float>* deadzone, HUD* hud):
    m_hud(hud),
    m_actions(actions),
    m_secondaryInputValues(secondaryInputValues)
{
    prop_deadzoneGamepad = deadzone;
    m_primaryConfigurationState = -1;
    m_secondaryConfigurationState = -1;
}

bool InputConfigurator::setActionInputMapping(ActionKeyMapping* action, bool primary) {
    if (isLastInputValid(primary)) {
        action->setMapping(lastInput(primary), primary);
        setLastInput(InputMapping(), primary);
        return true;
    }
    return false;
}

bool InputConfigurator::isKeyPressed(bool primary) {
    if (primary) {
        return lastInput(primary).type() != InputType::None;
    }
    else {
        for (int i = 0; i < m_secondaryInputValues->buttonCnt; i++) { // get pushed button
            if (m_secondaryInputValues->buttonValues[i] == GLFW_PRESS) {
                return true;
            }
        }
        for (int i = 0; i < m_secondaryInputValues->axisCnt; i++) { // get pushed axes
            if (glm::abs(m_secondaryInputValues->axisValues[i] - m_idleValues[i]) > *prop_deadzoneGamepad) {
                return true;
            }
        }
        return false;
    }
}

bool InputConfigurator::isLastInputValid(bool primary) {
    if (primary) {
        return lastInput(primary).type() != InputType::None;
    } else {
        for (int i = 0; i < m_secondaryInputValues->buttonCnt; i++) { // get pushed button
            if (m_secondaryInputValues->buttonValues[i] == GLFW_PRESS) {
                lastInput(primary) = InputMapping(InputType::GamePadKey, i, 1, 0.0f);
                return true;
            }
        }
        for (int i = 0; i < m_secondaryInputValues->axisCnt; i++) { // get pushed axes
            if (glm::abs(m_secondaryInputValues->axisValues[i] - m_idleValues[i]) > *prop_deadzoneGamepad) {
                // greater maxValue for same axes
                if (lastInput(primary).index() == i) {
                    if (glm::abs(lastInput(primary).maxValue() - m_idleValues[i]) <= glm::abs(m_secondaryInputValues->axisValues[i] - m_idleValues[i])) {
                        setLastInput(InputMapping(InputType::GamePadAxis, i, m_secondaryInputValues->axisValues[i], m_idleValues[i]),primary);
                        return false;
                    } else {
                        return true;
                    }
                } else {
                    setLastInput(InputMapping(InputType::GamePadAxis, i, m_secondaryInputValues->axisValues[i], m_idleValues[i]),primary);
                    return false;
                }
            }
        }
        return false;
    }
}

bool InputConfigurator::isConfiguring() {
    return m_primaryConfigurationState >= 0 || m_secondaryConfigurationState >= 0;
}

void InputConfigurator::startConfiguration(bool primary) {
    if (primary) {
        glow::info("Starting configuration for primary input device (keyboard), Please follow the instructions");
    } else {
        glow::info("Starting configuration for secondary input device (gamepad/Joystick), Please follow the instructions");
        m_idleValues.resize(m_secondaryInputValues->axisCnt);
        for(int a = 0; a < m_secondaryInputValues->axisCnt; a++) {
            m_idleValues[a] = m_secondaryInputValues->axisValues[a];
        }
    }
    setConfigurationState(0, primary);
    m_displayedInstructions = false;
    m_displayedKeyPressedWarning = false;
    m_beginningKeyConfiguration = true;
}

void InputConfigurator::update() {
    updateConfiguration(true);
    updateConfiguration(false);
}

void InputConfigurator::updateConfiguration(bool primary) {
    if (configurationState(primary) >= 0) {
        setupControls(primary);
    }
}

void InputConfigurator::setupControls(bool primary) {
    if (!m_displayedInstructions) {
        glow::info("Please press Key for action: %;", m_actions->at(m_primaryConfigurationState)->name());
        m_displayedInstructions = true;
    }
    if (m_beginningKeyConfiguration) {
        if (isKeyPressed(primary)) {
            if (!m_displayedKeyPressedWarning) {
                glow::info("Please release all buttons before setting a new key mapping");
                m_displayedKeyPressedWarning = true;
            }
            return;
        } else {
            m_beginningKeyConfiguration = false;
        }
    }
    if (!isLastInputValid(primary)) {
        return;
    }
    m_actions->at(configurationState(primary))->setMapping(lastInput(primary), primary);
    setLastInput(InputMapping(),primary);
    incrementConfigurationState(primary);
    if (configurationState(primary) >= m_actions->size()) {
        glow::info("Joystick setup complete");
        setConfigurationState(-1,primary);
    }
    m_beginningKeyConfiguration = true;
    m_displayedKeyPressedWarning = false;
    m_displayedInstructions = false;
}

void InputConfigurator::setActions(std::vector<ActionKeyMapping*>* m_actions) {
    this->m_actions = m_actions;
}

void InputConfigurator::setSecondaryInputValues(SecondaryInputValues* values) {
    m_secondaryInputValues = values;
}

void InputConfigurator::setLastInput(InputMapping lastInput, bool primary) {
    if (primary) {
        lastPrimaryInput = lastInput;
    } else {
        lastSecondaryInput = lastInput;
    }
}

InputMapping InputConfigurator::lastInput(bool primary) {
    if (primary) {
        return lastPrimaryInput;
    } else {
        return lastSecondaryInput;
    }
}

int InputConfigurator::configurationState(bool primary) {
    if (primary) {
        return m_primaryConfigurationState;
    } else {
        return m_secondaryConfigurationState;
    }
}

void InputConfigurator::incrementConfigurationState(bool primary) {
    if (primary) {
        m_primaryConfigurationState++;
    } else {
        m_secondaryConfigurationState++;
    }
}

void InputConfigurator::setConfigurationState(int state, bool primary) {
    if (primary) {
        m_primaryConfigurationState = state;
    } else {
        m_secondaryConfigurationState = state;
    }
}