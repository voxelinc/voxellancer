#pragma once
#include <map>

#include <glow/logging.h>

#include "property.hpp"

template <class T> 
class PropertyCollection {

public:
    PropertyCollection();
    virtual ~PropertyCollection();

    void registerProp(Property<T> * prop);
    void unregisterProp(Property<T> * prop);
    void update(std::string key, T value);

private:
    std::map<std::string, T> m_values;
    std::multimap<std::string, Property<T> *> m_properties;
};


template <class T>
void PropertyCollection<T>::update(std::string key, T value) {
    m_values[key] = value;
    auto result = m_properties.equal_range(key);
    for (auto iter = result.first; iter != result.second; ++iter)
    {
        Property<T> * prop = (*iter).second;
        prop->set(value);
    }
}


template <class T>
PropertyCollection<T>::PropertyCollection() :
m_values(),
m_properties()
{

}

template <class T>
PropertyCollection<T>::~PropertyCollection()
{

}


template <class T>
void PropertyCollection<T>::registerProp(Property<T> * prop)
{
    m_properties.insert(std::pair<std::string, Property<T> *>(prop->name(), prop));
    auto iter = m_values.find(prop->name());
    if (iter != m_values.end()) {
        prop->set(iter->second);
    }
    else {
        glow::warning("PropertyCollection: could not find a value for %s", prop->name());
    }
}

template <class T>
void PropertyCollection<T>::unregisterProp(Property<T> * prop)
{
    auto iter = m_properties.find(prop->name());
    for (; iter != m_properties.end(); ++iter) {
        if (iter->second == prop) {
            m_properties.erase(iter);
            break;
        }
    }
}
