#pragma once

#include <list>
#include <memory>
#include <stdint.h>
#include <string>

#include <glm/glm.hpp>

#include <glow/Changeable.h>
#include <unordered_map>
#include <map>


class InputMapping;

template<typename T> class Property;
template<typename T> class PropertyCollection;
class AbstractPropertyCollection;

namespace {
    struct compareTypeInfo {
        bool operator ()(const type_info* a, const type_info* b) const {
            return a->before(*b);
        }
    };
}

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
    template<typename T>
    void addPropertyCollection(PropertyCollection<T>* collection);

    std::unordered_map<const std::type_info*, std::unique_ptr<AbstractPropertyCollection>> m_propertyCollections;

    static PropertyManager* s_instance;
};

#include "propertymanager.inl"
