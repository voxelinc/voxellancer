#pragma once

#include "propertyimpl.h"


template<typename T>
PropertyCollection<T>::PropertyCollection(regexns::regex regex, std::function<T (const std::string&)> converter) :
    m_values(),
    m_properties(),
    m_regex(regex),
    m_converter(converter)
{
}

template<typename T>
T PropertyCollection<T>::get(const std::string& name) const {
    auto iter = m_values.find(name);
    if (iter != m_values.end()) {
        return iter->second;
    } else {
        glow::debug("PropertyCollection: could not get a '%;' value for %;", typeid(T).name(), name);
        return T();
    }
}

template<typename T>
T PropertyCollection<T>::get(const std::string& name, const T& defaultValue) const {
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
    getOrCreate(key)->set(value);
}

template<typename T>
PropertyImpl<T>* PropertyCollection<T>::getImpl(const std::string& key) {
    PropertyImpl<T>* impl = m_properties[key];
    if (impl) {
        return impl;
    } else {
        glow::debug("PropertyCollection: could not find a '%;' value for %;", typeid(T).name(), key);
        return new PropertyImpl<T>(key);
    }
}

template<typename T>
PropertyImpl<T>* PropertyCollection<T>::getImpl(const std::string& key, const T& defaultValue) {
    PropertyImpl<T>* impl = m_properties[key];
    if (impl == nullptr) {
        impl = create(key);
        impl->set(defaultValue);
    }
    return impl;
}

template <class T>
PropertyImpl<T>* PropertyCollection<T>::getOrCreate(const std::string& key) {
    auto impl = m_properties[key];
    if (impl) {
        return impl;
    } else {
        return create(key);
    }
}

template <class T>
PropertyImpl<T>* PropertyCollection<T>::create(const std::string& key) {
    assert(m_properties[key] == nullptr);

    PropertyImpl<T>* impl = new PropertyImpl<T>(key);
    m_properties[key] = impl;
    return impl;
}

