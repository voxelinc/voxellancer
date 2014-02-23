#pragma once

#include <list>
#include <memory>
#include <stdint.h>
#include <string>

#include <glm/glm.hpp>

#include <glow/Changeable.h>


class InputMapping;

template<typename T> class Property;
template<typename T> class PropertyCollection;

/*
 Keeps track of properties and loads ini files.
 Properties will be updated when a new ini file is loaded.
 Implements glow::Changeable, so glow::ChangeListener can
 be notified about changes.
*/
class PropertyManager : public glow::Changeable {
public:
    PropertyManager();
    virtual ~PropertyManager();

    void load(const std::string& file, const std::string& prefix = "");

    template<typename T> void registerProperty(Property<T>* prop);
    template<typename T> void registerProperty(Property<T>* prop, const T& defaultValue);

    template<typename T> void unregisterProperty(Property<T>* prop);

    static PropertyManager* instance();
    static void reset();

    template<typename T> T get(const std::string& name);
    template<typename T> T get(const std::string& name, const T& defaultValue);


protected:
    template<typename T>
    PropertyCollection<T>* getPropertyCollection();

    std::unique_ptr<PropertyCollection<float>> m_floatProperties;
    std::unique_ptr<PropertyCollection<int>> m_intProperties;
    std::unique_ptr<PropertyCollection<uint32_t>> m_uint32Properties;
    std::unique_ptr<PropertyCollection<char>> m_charProperties;
    std::unique_ptr<PropertyCollection<bool>> m_boolProperties;
    std::unique_ptr<PropertyCollection<std::string>> m_stringProperties;
    std::unique_ptr<PropertyCollection<glm::vec2>> m_vec2Properties;
    std::unique_ptr<PropertyCollection<glm::vec3>> m_vec3Properties;
    std::unique_ptr<PropertyCollection<glm::vec4>> m_vec4Properties;
    std::unique_ptr<PropertyCollection<InputMapping>> m_inputMappingProperties;
    std::unique_ptr<PropertyCollection<std::list<std::string>>> m_listProperties;

    static PropertyManager* s_instance;
};


#include "propertymanager.inl"
