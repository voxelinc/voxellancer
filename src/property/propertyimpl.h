#pragma once

#include <string>


template <class T>
class PropertyImpl {
public:
    PropertyImpl(const std::string& name);
    PropertyImpl(const std::string& name, const T& value);

    const std::string& name() const;

    const T& get() const;
    void set(const T& value);

protected:
    std::string m_name;
    T m_value;

};

#include "propertyimpl.inl"
