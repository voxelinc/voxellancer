#pragma once

#include "propertycollection.h"


template<typename T>
void PropertyManager::registerProperty(Property<T>* prop) {
    getPropertyCollection(prop)->registerProperty(prop);
}

template<typename T>
void PropertyManager::unregisterProperty(Property<T>* prop) {
    getPropertyCollection(prop)->unregisterProperty(prop);
}

template<typename T>
T PropertyManager::get(const std::string& name) {
    return getPropertyCollection<T>(nullptr)->get(name);
}

template<typename T>
T PropertyManager::get(const std::string& name, const T& defaultValue) {
    return getPropertyCollection<T>(nullptr)->get(name, defaultValue);
}

