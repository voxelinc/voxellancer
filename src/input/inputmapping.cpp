#include "inputmapping.h"


InputMapping::InputMapping(InputType type, int index, float maxValue, float idleValue) :
    m_type(type),
    m_index(index),
    m_maxValue(maxValue),
    m_idleValue(idleValue)
{
}

InputMapping::InputMapping():
    InputMapping(InputType::None, 0, 0.0f, 0.0f)
{

}

InputType InputMapping::type() {
    return m_type;
}

int InputMapping::index() {
    return m_index;
}

float InputMapping::maxValue() {
    return m_maxValue;
}

float InputMapping::idleValue() {
    return m_idleValue;
}

