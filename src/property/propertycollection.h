#pragma once

#include <map>
#include <string>
#include <functional>

#include <glow/logging.h>

#include "def_regex.h"

class AbstractPropertyCollection {
public:
    virtual bool update(const std::string& key, const std::string& svalue) = 0;
};

template <class T>
class PropertyImpl;

template <class T>
class PropertyCollection : public AbstractPropertyCollection {
public:
    PropertyCollection(regexns::regex regex, std::function<T(const std::string&)> converter);

    PropertyImpl<T>* getImpl(const std::string& key);
    PropertyImpl<T>* getImpl(const std::string& key, const T& defaultValue);

    virtual bool update(const std::string& key, const std::string& svalue) override;

    void set(const std::string& key, const T& value);

    T get(const std::string& name) const;
    T get(const std::string& name, const T& defaultValue) const;


protected:
    std::map<std::string, T> m_values;
    std::map<std::string, PropertyImpl<T>*> m_properties;
    regexns::regex m_regex;
    std::function<T(const std::string&)> m_converter;

    PropertyImpl<T>* getOrCreate(const std::string& key);
    PropertyImpl<T>* create(const std::string& key);
};

#include "propertycollection.inl"
