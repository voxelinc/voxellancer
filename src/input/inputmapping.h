#pragma once


enum class InputType {
    None = 0,
    Keyboard,
    GamePadKey,
    GamePadAxis
};

class InputMapping {
public:
    InputMapping();
    InputMapping(InputType type, int index, float maxValue, float idleValue);

    InputType type();
    int index();
    float maxValue();
    float idleValue();

private:
    InputType m_type;
    int m_index;
    float m_maxValue;
    float m_idleValue;
};

