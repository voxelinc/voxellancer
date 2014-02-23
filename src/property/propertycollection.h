#pragma once

#include <map>
#include <string>
#include <functional>

#include <glow/logging.h>

#include "def_regex.h"


template <class T>
class Property;

template <class T>
class PropertyCollection {
public:
    PropertyCollection(regexns::regex regex, std::function<T(const std::string&)> converter);
    virtual ~PropertyCollection();

    void registerProperty(Property<T> * prop);
    void registerProperty(Property<T> * prop, const T& defaultValue);

    void unregisterProperty(Property<T> * prop);

    bool update(const std::string& key, const std::string& svalue);

    void set(const std::string& key, const T& value);

    T get(const std::string& name) const;
    T get(const std::string& name, const std::string& defaultValue) const;


private:
    std::map<std::string, T> m_values;
    std::multimap<std::string, Property<T> *> m_properties;
    regexns::regex m_regex;
    std::function<T(const std::string&)> m_converter;
};

#include "propertycollection.inl"
