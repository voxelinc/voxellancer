#pragma once

#include <string>

#include <glm/glm.hpp>
#include <glow/Changeable.h>

#include "property.hpp"
#include "propertycollection.hpp"


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
    void registerProp(Property<T> * prop);
    template <class T>
    void unregisterProp(Property<T> * prop);
    
    static PropertyManager * getInstance();
    static void clear();

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
void PropertyManager::registerProp(Property<T> * prop)
{
    getPropertyCollection(prop)->registerProp(prop);
}

template <class T>
void PropertyManager::unregisterProp(Property<T> * prop)
{
    getPropertyCollection(prop)->unregisterProp(prop);
}

