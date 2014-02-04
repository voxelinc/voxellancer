#include "range.h"

#include <algorithm>
#include <cassert>


Range::Range():
    Range(0.0f, 0.0f)
{
}

Range::Range(float min, float max):
    m_min(min),
    m_max(max)
{
    assert(min <= max);
}

float Range::min() const {
    return m_min;
}

void Range::setMin(float min) {
    m_min = min;
}

float Range::max() const {
    return m_max;
}

void Range::setMax(float max) {
    m_max = max;
}

float Range::clamp(float value) {
    return std::max(std::min(value, m_max), m_min);
}


