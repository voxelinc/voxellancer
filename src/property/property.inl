#pragma once

#include "propertymanager.h"

template <class T>
Property<T>::Property(char * name) :
    m_name(name),
    m_value()
{
    PropertyManager::instance()->registerProperty(this);
}

template <class T>
Property<T>::~Property()
{
    PropertyManager::instance()->unregisterProperty(this);
}

template <class T>
char * Property<T>::name()
{
    return m_name;
}

template <class T>
T Property<T>::get()
{
    return m_value;
}

template <class T>
void Property<T>::set(T value)
{
    m_value = value;
}

template <class T>
Property<T>::operator T()
{
    return m_value;
}

template <class T>
T* Property<T>::operator->() {
    {
        return &m_value;
    }
}
