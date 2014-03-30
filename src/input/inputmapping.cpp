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

InputType InputMapping::type() const {
    return m_type;
}

int InputMapping::index() const {
    return m_index;
}

float InputMapping::maxValue() const {
    return m_maxValue;
}

float InputMapping::idleValue() const {
    return m_idleValue;
}

