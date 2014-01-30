#pragma once

#include <string>


template <class T>
class Property {
public:
    Property(const std::string& name);
    virtual ~Property();

    const std::string& name();

    T get();
    void set(T value);

    T* operator->();
    operator T();

    static T get(const std::string& name);


private:
    std::string m_name;
    T m_value;
};

#include "property.inl"
