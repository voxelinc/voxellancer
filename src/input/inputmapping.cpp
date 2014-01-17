#include "inputmapping.h"


InputMapping::InputMapping(InputType type, int index, float maxValue) :
m_type(type),
m_index(index),
m_maxValue(maxValue) {

}

InputMapping::InputMapping() :InputMapping(InputType::None, 0, 0.0f) {

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
