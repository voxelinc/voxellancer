#pragma once


template <class T> 
class Property {

public:
    Property(char * name);
    virtual ~Property();

    operator T();

    char * name();
    T get();
    void set(T value);
    char * m_name;

private:
    T m_value;
};

template <class T>
Property<T>::Property(char * name) :
    m_name(name),
    m_value()
{
    PropertyManager::getInstance()->registerProp(this);
}

template <class T>
Property<T>::~Property()
{
    PropertyManager::getInstance()->unregisterProp(this);
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