#pragma once

#include <string>

#include "property/property.h"
#include "input/inputmapping.h"


class ActionKeyMapping {
public:
    ActionKeyMapping(std::string primary, std::string secondary, std::string name);
    ActionKeyMapping(std::string primary, std::string secondary, std::string name, bool toggleAction);

    InputMapping mapping(InputClass inputClass);
    void setMapping(InputClass inputClass, InputMapping mapping);

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