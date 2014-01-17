#pragma once

template <class T> 
class Property {

public:
    Property(char * name);
    virtual ~Property();

    operator T();

    char* name();
    T get();
    void set(T value);

    T* operator->();

    static T get(char* name);

private:
    char * m_name;
    T m_value;
};

#include "property.inl"