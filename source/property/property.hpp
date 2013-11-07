#pragma once

#include "property/propertymanager.h"

template <class T> 
class Property {

public:
    Property(char * name);
    virtual ~Property();

    operator T();

    char * name();
    T get();
    void set(T value);

private:
    char * m_name;
    T m_value;
};

template <class T>
Property<T>::Property(char * name) :
    m_name(name),
    m_value()
{
    PropertyManager::getInstance()->registerProperty(this);
}

template <class T>
Property<T>::~Property()
{
    PropertyManager::getInstance()->unregisterProperty(this);
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