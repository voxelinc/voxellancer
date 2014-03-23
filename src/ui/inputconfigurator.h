#pragma once

#include <vector>

#include "input/inputmapping.h"
#include "property/property.h"


class ActionKeyMapping;
struct SecondaryInputValues;

class HUD;

class InputConfigurator {
public:
    InputConfigurator(std::vector<ActionKeyMapping*>* actions, SecondaryInputValues *secondaryInputValues, Property<float>* deadzone, HUD* hud);

    void startConfiguration(InputClass inputClass);
    bool isConfiguring();
    void update();

    void setActions(std::vector<ActionKeyMapping*>* actions);

    void setSecondaryInputValues(SecondaryInputValues* values);

    void setLastInput(InputMapping lastInput, InputClass inputClass);

    InputMapping lastInput(InputClass inputClass);


private:
    std::vector<ActionKeyMapping*>* m_actions;
    SecondaryInputValues* m_secondaryInputValues;
    std::vector<float> m_idleValues;

    HUD* m_hud;

    Property<float>* prop_deadzoneGamepad;

    bool setActionInputMapping(ActionKeyMapping* action, InputClass inputClass);
    bool isLastInputValid(InputClass inputClass);

    bool isKeyPressed(InputClass inputClass);

    void setupControls(InputClass inputClass);

    void updateConfiguration(InputClass inputClass);

    InputMapping lastPrimaryInput;
    InputMapping lastSecondaryInput;

    int m_secondaryConfigurationState;
    int m_primaryConfigurationState;

    int configurationState(InputClass inputClass);
    void incrementConfigurationState(InputClass inputClass);
    void setConfigurationState(int state, InputClass inputClass);
    void writeConfig();
    bool m_beginningKeyConfiguration = true;
    bool m_displayedKeyPressedWarning = false;
    bool m_displayedInstructions = false;
};
