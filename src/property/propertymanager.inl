#pragma once

#include <stdexcept>

#include "propertycollection.h"


template<typename T>
PropertyImpl<T>* PropertyManager::getImpl(const std::string& key) {
    return getPropertyCollection<T>()->getImpl(key);
}

template<typename T>
PropertyImpl<T>* PropertyManager::getImpl(const std::string& key, const T& defaultValue) {
    return getPropertyCollection<T>()->getImpl(key, defaultValue);
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

