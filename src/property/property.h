#pragma once

#include <string>

template <class T>
class PropertyImpl;

/**
 * Represents a value loaded from an .ini file
 */
template <class T>
class Property {
public:
    Property(const std::string& name);
    Property(const std::string& name, const T& defaultValue);

    const std::string& name() const;

    const T& get() const;
    void set(const T& value);

    operator T() const;
    const T* operator->() const;

    static T get(const std::string& name);
    static T get(const std::string& name, const T& defaultvalue);

    static Property<T> unnamed(const T& value);

protected:
    PropertyImpl<T>* m_impl;

};

/**
 *  Helper method to get rid of the <T> as it can be inferred from the value
 */
template<class T>
Property<T> unnamedProperty(const T& value) {
    return Property<T>::unnamed(value);
}

#include "property.inl"
