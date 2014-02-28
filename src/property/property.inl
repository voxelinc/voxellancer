#pragma once

#include "propertymanager.h"


template <class T>
Property<T>::Property(const std::string& name):
    m_name(name),
    m_value()
{
    PropertyManager::instance()->registerProperty(this);
}

template <class T>
Property<T>::Property(const std::string& name, const T& defaultValue):
    m_name(name),
    m_value()
{
    PropertyManager::instance()->registerProperty(this, defaultValue);
}

template <class T>
Property<T>::~Property() {
    PropertyManager::instance()->unregisterProperty(this);
}

template <class T>
const std::string& Property<T>::name() const {
    return m_name;
}

template <class T>
T Property<T>::get() const {
    return m_value;
}

template <class T>
void Property<T>::set(const T& value) {
    m_value = value;
}

template <class T>
Property<T>::operator T() const {
    return m_value;
}

template <class T>
T* Property<T>::operator->() {
    return &m_value;
}

template <class T>
T Property<T>::get(const std::string& name) {
    return PropertyManager::instance()->get<T>(name);
}

template <class T>
T Property<T>::get(const std::string& name, const T& defaultvalue) {
    return PropertyManager::instance()->get<T>(name, defaultvalue);

}