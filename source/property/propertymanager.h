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

    void registerProp(Property<float> * prop);
    void registerProp(Property<int> * prop);
    void registerProp(Property<char> * prop);
    void registerProp(Property<bool> * prop);
    void registerProp(Property<std::string> * prop);
    void registerProp(Property<glm::vec3> * prop);
    
    void unregisterProp(Property<float> * prop);
    void unregisterProp(Property<int> * prop);
    void unregisterProp(Property<char> * prop);
    void unregisterProp(Property<bool> * prop);
    void unregisterProp(Property<std::string> * prop);
    void unregisterProp(Property<glm::vec3> * prop);

    static PropertyManager * getInstance();
    static void clear();

private:

    PropertyCollection<float> m_floatProperties;
    PropertyCollection<int> m_intProperties;
    PropertyCollection<char> m_charProperties;
    PropertyCollection<bool> m_boolProperties;
    PropertyCollection<std::string> m_stringProperties;
    PropertyCollection<glm::vec3> m_vec3Properties;
        
    static PropertyManager * s_instance;
};

