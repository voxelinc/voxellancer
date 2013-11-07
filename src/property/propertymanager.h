#pragma once

#include <string>

#include <glm/glm.hpp>

#include <glow/Changeable.h>

#include "propertycollection.h"

template <class T>
class Property;

/**
* Keeps track of properties and loads ini files.
* Properties will be updated when a new ini file is loaded.
*
* Implements glow::Changeable, so glow::ChangeListener can 
* be notified about changes.
**/
class PropertyManager : public glow::Changeable {

public:
    PropertyManager();
    virtual ~PropertyManager();
    
    void load(std::string file);

    template <class T>
    void registerProperty(Property<T> * prop);
    template <class T>
    void unregisterProperty(Property<T> * prop);
    
    static PropertyManager * getInstance();
    static void reset();

private:
    template <class T>
    PropertyCollection<T> * getPropertyCollection(Property<T> * prop);

    PropertyCollection<float> m_floatProperties;
    PropertyCollection<int> m_intProperties;
    PropertyCollection<char> m_charProperties;
    PropertyCollection<bool> m_boolProperties;
    PropertyCollection<std::string> m_stringProperties;
    PropertyCollection<glm::vec3> m_vec3Properties;
        
    static PropertyManager * s_instance;
};

template <class T>
void PropertyManager::registerProperty(Property<T> * prop)
{
    getPropertyCollection(prop)->registerProperty(prop);
}

template <class T>
void PropertyManager::unregisterProperty(Property<T> * prop)
{
    getPropertyCollection(prop)->unregisterProperty(prop);
}

