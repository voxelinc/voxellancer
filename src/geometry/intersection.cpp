#include "intersection.h"


Intersection::Intersection() = default;

Intersection::Intersection(bool is):
    m_is(is)
{

}

Intersection::~Intersection() = default;

bool Intersection::is() const {
    return m_is;
}

Intersection::operator bool() const {
    return m_is;
}

