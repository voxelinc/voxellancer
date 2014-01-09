#pragma once


enum InputType {
    None,
    Keyboard,
    GamePadKey,
    GamePadAxis
};

class InputMapping {
public:
    InputMapping();
    InputMapping(InputType type, int index, float maxValue);
    InputType type();
    int index();
    float maxValue();

private:
    InputType m_type;
    int m_index;
    float m_maxValue;
};