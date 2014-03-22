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

    void setLastInput(InputClass inputClass, InputMapping lastInput);

    const InputMapping& lastInput(InputClass inputClass);


private:
    std::vector<ActionKeyMapping*>* m_actions;
    SecondaryInputValues* m_secondaryInputValues;
    std::vector<float> m_idleValues;

    HUD* m_hud;

    Property<float>* prop_deadzoneGamepad;

    InputMapping lastPrimaryInput;
    InputMapping lastSecondaryInput;

    int m_secondaryConfigurationState;
    int m_primaryConfigurationState;
    
    bool m_beginningKeyConfiguration = true;
    bool m_displayedInstructions = false;

    bool setActionInputMapping(InputClass inputClass, ActionKeyMapping* action);
    bool isLastInputValid(InputClass inputClass);

    bool isKeyPressed(InputClass inputClass);
    void setupControls(InputClass inputClass);
    void updateConfiguration(InputClass inputClass);

    int configurationState(InputClass inputClass);
    void incrementConfigurationState(InputClass inputClass);
    void setConfigurationState(int state, InputClass inputClass);

};
