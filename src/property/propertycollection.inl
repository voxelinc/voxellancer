#pragma once

#include "property.h"


template<typename T>
PropertyCollection<T>::PropertyCollection(regexns::regex regex, std::function<T (const std::string&)> converter) :
    m_values(),
    m_properties(),
    m_regex(regex),
    m_converter(converter)
{
}

template<typename T>
PropertyCollection<T>::~PropertyCollection() {
}

template<typename T>
T PropertyCollection<T>::get(const std::string& name) const {
    auto iter = m_values.find(name);
    if (iter != m_values.end()) {
        return iter->second;
    } else {
        glow::debug("PropertyCollection: could not find a '%;' value for %;", typeid(T).name(), name);
        return T();
    }
}

template<typename T>
T PropertyCollection<T>::get(const std::string& name, const std::string& defaultValue) const {
    auto iter = m_values.find(name);
    if (iter != m_values.end()) {
        return iter->second;
    } else {
        return defaultValue;
    }
}

template<typename T>
bool PropertyCollection<T>::update(const std::string& key, const std::string& svalue) {
    if (!regexns::regex_match(svalue, m_regex)) {
        return false;
    }

    set(key, m_converter(svalue));
    return true;
}


template<typename T>
void PropertyCollection<T>::set(const std::string& key, const T& value) {
    m_values[key] = value;

    auto result = m_properties.equal_range(key);

    for (auto iter = result.first; iter != result.second; ++iter)
    {
        Property<T>* prop = iter->second;
        prop->set(value);
    }
}

template<typename T>
void PropertyCollection<T>::registerProperty(Property<T>* prop) {
    m_properties.insert(std::pair<std::string, Property<T> *>(prop->name(), prop));
    auto iter = m_values.find(prop->name());
    if (iter != m_values.end()) {
        prop->set(iter->second);
    } else {
        glow::debug("PropertyCollection: could not find a '%;' value for %;", typeid(T).name(), prop->name());
    }
}

template<typename T>
void PropertyCollection<T>::registerProperty(Property<T>* prop, const T& defaultValue) {
    m_properties.insert(std::pair<std::string, Property<T> *>(prop->name(), prop));
    auto iter = m_values.find(prop->name());
    if (iter != m_values.end()) {
        prop->set(iter->second);
    } else {
        set(prop->name(), defaultValue);
        registerProperty(prop);
    }
}

template<typename T>
void PropertyCollection<T>::unregisterProperty(Property<T>* prop) {
    auto iter = m_properties.find(prop->name());
    for (; iter != m_properties.end(); ++iter) {
        if (iter->second == prop) {
            m_properties.erase(iter);
            break;
        }
    }
}


