#pragma once

#include "propertycollection.h"


template<typename T>
void PropertyManager::registerProperty(Property<T>* prop) {
    getPropertyCollection<T>()->registerProperty(prop);
}

template<typename T>
void PropertyManager::registerProperty(Property<T>* prop, const T& defaultValue) {
    getPropertyCollection<T>()->registerProperty(prop, defaultValue);
}

template<typename T>
void PropertyManager::unregisterProperty(Property<T>* prop) {
    getPropertyCollection<T>()->unregisterProperty(prop);
}

template<typename T>
T PropertyManager::get(const std::string& name) {
    return getPropertyCollection<T>(nullptr)->get(name);
}

template<typename T>
T PropertyManager::get(const std::string& name, const T& defaultValue) {
    return getPropertyCollection<T>(nullptr)->get(name, defaultValue);
}

