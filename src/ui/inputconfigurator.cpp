#include "inputconfigurator.h"

#include "ui/hud.h"


InputConfigurator::InputConfigurator(std::vector<ActionKeyMapping*>* actions, SecondaryInputValues *secondaryInputValues, Property<float>* deadzone, HUD* hud) {
    this->hud = hud;
    this->actions = actions;
    this->secondaryInputValues = secondaryInputValues;
    prop_deadzoneGamepad = deadzone;
    primaryConfigurationState = -1;
    secondaryConfigurationState = -1;
}

bool InputConfigurator::setActionInputMapping(ActionKeyMapping* action, bool primary) {
    if (primary) {
        if (isLastPrimaryInputValid()) {
            action->primaryMapping.set(lastPrimaryInput);
            lastPrimaryInput = InputMapping();
            return true;
        }
    } else {
        if (isLastSecondaryInputValid()) {
            action->secondaryMapping.set(lastSecondaryInput);
            lastSecondaryInput = InputMapping();
            return true;
        }
    }
    return false;
}

bool InputConfigurator::isSecondaryInput() {

    bool valid = false;

    for (int i = 0; i < secondaryInputValues->buttonCnt; i++) { // get pushed button
        if (secondaryInputValues->buttonValues[i] == GLFW_PRESS) {
            valid = true;
        }
    }
    for (int i = 0; i < secondaryInputValues->axisCnt; i++) { // get pushed axes
        if (glm::abs(secondaryInputValues->axisValues[i]) > *prop_deadzoneGamepad) {
            valid = true;
        }
    }
    return valid;
}

bool InputConfigurator::isPrimaryInput() {
    if (lastPrimaryInput.index() == InputType::None) {
        return false;
    }
    return true;
}

bool InputConfigurator::isLastSecondaryInputValid() {

    for (int i = 0; i < secondaryInputValues->buttonCnt; i++) { // get pushed button
        if (secondaryInputValues->buttonValues[i] == GLFW_PRESS) {
            lastSecondaryInput = InputMapping(InputType::GamePadKey, i, 1);
            return true;
        }
    }
    for (int i = 0; i < secondaryInputValues->axisCnt; i++) { // get pushed axes
        if (glm::abs(secondaryInputValues->axisValues[i]) > *prop_deadzoneGamepad) {
            // greater maxValue for same axes
            if (lastSecondaryInput.index() == i) {
                if (glm::abs(lastSecondaryInput.maxValue()) <= glm::abs(secondaryInputValues->axisValues[i])) {
                    lastSecondaryInput = InputMapping(InputType::GamePadAxis, i, secondaryInputValues->axisValues[i]);
                    return false;
                } else {
                    return true;
                }
            } else {
                lastSecondaryInput = InputMapping(InputType::GamePadAxis, i, secondaryInputValues->axisValues[i]);
                return false;
            }
        }
    }
    return false;
}

bool InputConfigurator::isLastPrimaryInputValid() {
    if (lastPrimaryInput.type() == InputType::None) {
        return false;
    }
    return true;
}

bool InputConfigurator::isConfiguring() {
    if (primaryConfigurationState >= 0) {
        return true;
    }
    if (secondaryConfigurationState >= 0) {
        return true;
    }
    return false;
}

void InputConfigurator::startConfiguration(bool primary) {
    if (primary) {
        hud->printLine("Starting configuration for primary input device (keyboard), Please follow the instructions");
        primaryConfigurationState = 0;
    } else {
        hud->printLine("Starting configuration for secondary input device (gamepad/Joystick), Please follow the instructions");
        secondaryConfigurationState = 0;
    }
    displayedInstructions = false;
    displayedKeyPressedWarning = false;
    beginningKeyConfiguration = true;
}

void InputConfigurator::update() {
    if (primaryConfigurationState >= 0) {
        setupPrimaryControls();
    }
    if (secondaryConfigurationState >= 0) {
        setupSecondaryControls();
    }
}

void InputConfigurator::setupPrimaryControls() {
    if (!displayedInstructions) {
        hud->printLine("Please press Joystick button or axis for action: " + actions->at(primaryConfigurationState)->name);
        displayedInstructions = true;
    }
    if (beginningKeyConfiguration) {
        if (isSecondaryInput()) {
            if (!displayedKeyPressedWarning) {
                hud->printLine("Please release all buttons before setting a new key mapping");
                displayedKeyPressedWarning = true;
            }
            return;
        } else {
            beginningKeyConfiguration = false;
        }
    }
    if (!isLastPrimaryInputValid()) {
        return;
    }
    actions->at(primaryConfigurationState)->primaryMapping.set(lastPrimaryInput);
    lastPrimaryInput = InputMapping();
    primaryConfigurationState++;
    if (primaryConfigurationState >= actions->size()) {
        hud->printLine("Joystick setup complete");
        primaryConfigurationState = -1;
    }
    beginningKeyConfiguration = true;
    displayedKeyPressedWarning = false;
    displayedInstructions = false;
}

void InputConfigurator::setupSecondaryControls() {
    if (!displayedInstructions) {
        hud->printLine("Please press Joystick button or axis for action: " + actions->at(secondaryConfigurationState)->name);
        displayedInstructions = true;
    }
    if (beginningKeyConfiguration) {
        if (isSecondaryInput()) {
            if (!displayedKeyPressedWarning) {
                hud->printLine("Please release all buttons before setting a new key mapping");
                displayedKeyPressedWarning = true;
            }
            return;
        } else {
            beginningKeyConfiguration = false;
        }
    }
    if (!isLastSecondaryInputValid()) {
        return;
    }
    actions->at(secondaryConfigurationState)->secondaryMapping.set(lastSecondaryInput);
    lastSecondaryInput = InputMapping();
    secondaryConfigurationState++;
    if (secondaryConfigurationState >= actions->size()) {
        hud->printLine("Joystick setup complete");
        secondaryConfigurationState = -1;
    }
    beginningKeyConfiguration = true;
    displayedKeyPressedWarning = false;
    displayedInstructions = false;
}

void InputConfigurator::setLastPrimaryInput(InputMapping lastInput) {
    lastPrimaryInput = lastInput;
}

void InputConfigurator::setLastSecondaryInput(InputMapping lastInput) {
    lastSecondaryInput = lastInput;
}

void InputConfigurator::setActions(std::vector<ActionKeyMapping*>* actions) {
    this->actions = actions;
}

void InputConfigurator::setSecondaryInputValues(SecondaryInputValues* values) {
    secondaryInputValues = values;
}