#pragma once

template <class T>
class Property {
public:
    Property(char * name);
    virtual ~Property();

    const char* name() const;
    T get() const;
    void set(T value);

    operator T() const;
    T* operator->();

    static T get(const char* name);


protected:
    char* m_name;
    T m_value;
};

#include "property.inl"
