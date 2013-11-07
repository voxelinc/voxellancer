#pragma once
#include <map>
#include <regex>
#include <functional>

#include <glow/logging.h>

template <class T>
class Property;

template <class T> 
class PropertyCollection {

public:
    PropertyCollection(std::regex regex, std::function<T(const std::string&)> converter);
    virtual ~PropertyCollection();

    void registerProperty(Property<T> * prop);
    void unregisterProperty(Property<T> * prop);
    bool update(const std::string & key, const std::string & svalue);

private:
    std::map<std::string, T> m_values;
    std::multimap<std::string, Property<T> *> m_properties;
    std::regex m_regex;
    std::function<T(const std::string&)> m_converter;

};

#include "propertycollection.inl"