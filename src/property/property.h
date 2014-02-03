#pragma once

#include <string>


template <class T>
class Property {
public:
    Property(const std::string& name);
    virtual ~Property();

    const std::string& name();

    T get() const;
    void set(T value);

    operator T() const;
    T* operator->();

    static T get(const std::string& name);


protected:
    std::string m_name;
    T m_value;
};

#include "property.inl"
