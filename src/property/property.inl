#pragma once

#include "propertymanager.h"

template <class T>
Property<T>::Property(char * name) :
    m_name(name),
    m_value()
{
    PropertyManager::instance()->registerProperty(this);
    glow::warning("Property.inl: dont use default constructor until linux is fixed!");
}

template <class T>
Property<T>::Property(char * name, T defaultValue) :
    m_name(name),
    m_value(defaultValue)
{
// TODO: REMOVE WHEN LINUX IS WORKING
#ifdef WIN32
    PropertyManager::instance()->registerProperty(this);
#endif
}

template <class T>
Property<T>::~Property()
{
#ifdef WIN32
    PropertyManager::instance()->unregisterProperty(this);
#endif
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