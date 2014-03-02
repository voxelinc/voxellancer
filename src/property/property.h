#pragma once

#include <string>


template <class T>
class Property {
public:
    Property(const std::string& name);
    Property(const std::string& name, const T& defaultValue);
    virtual ~Property();

    const std::string& name() const;

    T get() const;
    void set(const T& value);

    operator T() const;
    T* operator->();

    static T get(const std::string& name);
    static T get(const std::string& name, const T& defaultvalue);


protected:
    std::string m_name;
    T m_value;
};



#include "property.inl"
