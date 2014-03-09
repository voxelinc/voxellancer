#pragma once

#include <stdexcept>

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
    return getPropertyCollection<T>()->get(name);
}

template<typename T>
T PropertyManager::get(const std::string& name, const T& defaultValue) {
    return getPropertyCollection<T>()->get(name, defaultValue);
}

template <typename T>
PropertyCollection<T>* PropertyManager::getPropertyCollection() {
    AbstractPropertyCollection* collection = m_propertyCollections[&typeid(T)].get();
    if (collection == nullptr) {
        glow::fatal("PropertyManager: Unregistered Type: %;", typeid(T).name());
        throw new std::runtime_error("PropertyManager: Unregistered Type");
    }
    PropertyCollection<T>* collectionT = dynamic_cast<PropertyCollection<T>*>(collection);
    assert(collectionT != nullptr);
    return collectionT;
}

template<typename T>
void PropertyManager::addPropertyCollection(PropertyCollection<T>* collection) {
    m_propertyCollections.insert(std::make_pair(&typeid(T), std::unique_ptr<AbstractPropertyCollection>(collection)));
}

