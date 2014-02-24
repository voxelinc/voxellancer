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

    void startConfiguration(bool primary);
    bool isConfiguring();
    void update();

    void setActions(std::vector<ActionKeyMapping*>* actions);

    void setSecondaryInputValues(SecondaryInputValues* values);

    void setLastInput(InputMapping lastInput, bool primary);

    InputMapping lastInput(bool primary);


private:
    std::vector<ActionKeyMapping*>* m_actions;
    SecondaryInputValues* m_secondaryInputValues;
    std::vector<float> m_idleValues;

    HUD* m_hud;

    Property<float>* prop_deadzoneMouse;
    Property<float>* prop_deadzoneGamepad;


    bool setActionInputMapping(ActionKeyMapping* action, bool primary);
    bool isLastInputValid(bool primary);

    bool isKeyPressed(bool primary);

    void setupControls(bool primary);

    void updateConfiguration(bool primary);

    InputMapping lastPrimaryInput;
    InputMapping lastSecondaryInput;

    int m_secondaryConfigurationState;
    int m_primaryConfigurationState;

    int configurationState(bool primary);
    void incrementConfigurationState(bool primary);
    void setConfigurationState(int state, bool primary);

    bool m_beginningKeyConfiguration = true;
    bool m_displayedKeyPressedWarning = false;
    bool m_displayedInstructions = false;
};
