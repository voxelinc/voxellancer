#pragma once

#include "property.h"

template <class T>
PropertyCollection<T>::PropertyCollection(regexns::regex regex, std::function<T (const std::string&)> converter) :
    m_values(),
    m_properties(),
    m_regex(regex),
    m_converter(converter)
{

}

template <class T>
PropertyCollection<T>::~PropertyCollection()
{

}

template <class T>
bool PropertyCollection<T>::update(const std::string & key, const std::string & svalue) {
    if (!regexns::regex_match(svalue, m_regex)) {
        return false;
    }

    T tvalue = m_converter(svalue);

    m_values[key] = tvalue;
    auto result = m_properties.equal_range(key);
    for (auto iter = result.first; iter != result.second; ++iter)
    {
        Property<T> * prop = (*iter).second;
        prop->set(tvalue);
    }
    return true;
}


template <class T>
void PropertyCollection<T>::registerProperty(Property<T> * prop)
{
    m_properties.insert(std::pair<std::string, Property<T> *>(prop->name(), prop));
    auto iter = m_values.find(prop->name());
    if (iter != m_values.end()) {
        prop->set(iter->second);
    }
    else {
        glow::debug("PropertyCollection: could not find a value for %;", prop->name());
    }
}


template <class T>
void PropertyCollection<T>::unregisterProperty(Property<T> * prop)
{
    auto iter = m_properties.find(prop->name());
    for (; iter != m_properties.end(); ++iter) {
        if (iter->second == prop) {
            m_properties.erase(iter);
            break;
        }
    }
}


