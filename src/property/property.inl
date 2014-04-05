#pragma once

#include "propertymanager.h"
#include "propertyimpl.h"


template <class T>
Property<T>::Property(const std::string& name):
    m_impl(nullptr)
{
    assert(name != "");
    m_impl = PropertyManager::instance()->getImpl<T>(name);
}

template <class T>
Property<T>::Property(const std::string& name, const T& defaultValue):
    m_impl(nullptr)
{
    if (name == "") {
        m_impl = new PropertyImpl<T>("", defaultValue);
    } else {
        m_impl = PropertyManager::instance()->getImpl<T>(name, defaultValue);
    }
}

template <class T>
const std::string& Property<T>::name() const {
    return m_impl->name();
}

template <class T>
const T& Property<T>::get() const {
    return m_impl->get();
}

template <class T>
void Property<T>::set(const T& value) {
    m_impl->set(value);
}

template <class T>
Property<T>::operator T() const {
    return m_impl->get();
}

template <class T>
const T* Property<T>::operator->() const {
    return &m_impl->get();
}

template <class T>
T Property<T>::get(const std::string& name) {
    return PropertyManager::instance()->get<T>(name);
}

template <class T>
T Property<T>::get(const std::string& name, const T& defaultvalue) {
    return PropertyManager::instance()->get<T>(name, defaultvalue);
}

template <class T>
Property<T> Property<T>::unnamed(const T& value) {
    return Property<T>("", value);
}
