#include "propertyimpl.h"

#include <string>



template <class T>
PropertyImpl<T>::PropertyImpl(const std::string& name) :
    m_name(name)
{
    assert(m_name != "");
}

template <class T>
PropertyImpl<T>::PropertyImpl(const std::string& name, const T& value) :
    m_name(name),
    m_value(value)
{
}

template <class T>
const std::string& PropertyImpl<T>::name() const {
    return m_name;
}

template <class T>
const T& PropertyImpl<T>::get() const {
    return m_value;
}

template <class T>
void PropertyImpl<T>::set(const T& value) {
    m_value = value;
}
