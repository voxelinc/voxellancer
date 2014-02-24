#pragma once

#include <string>

#include "property/property.h"
#include "input/inputmapping.h"


class ActionKeyMapping {
public:
    ActionKeyMapping(char* primary, char* secondary, std::string name);
    ActionKeyMapping(char* primary, char* secondary, std::string name, bool toggleAction);

    InputMapping mapping(bool primary);
    void setMapping(InputMapping mapping, bool primary);

    std::string name();
    bool toggleAction();
    bool toggleStatus();

    void setToggleStatus(bool status);

protected:
    Property<InputMapping> m_primaryMapping;
    Property<InputMapping> m_secondaryMapping;
    bool m_toggleAction;
    bool m_toggleStatus;
    std::string m_name;
};

struct SecondaryInputValues {
    int buttonCnt, axisCnt;
    const unsigned char *buttonValues;
    const float *axisValues;

    SecondaryInputValues();
};