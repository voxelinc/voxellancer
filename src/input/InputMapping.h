#pragma once


enum InputType {
    None,
    Keyboard,
    GamePad
};

class InputMapping {
public:
    InputMapping();
    InputMapping(InputType type, int index, float max_value);
    InputType type();
    int index();
    float maxValue();

private:
    InputType m_type;
    int m_index;
    float m_maxValue;
};