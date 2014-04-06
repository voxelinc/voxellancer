#pragma once

#include <list>
#include <memory>
#include <stdint.h>
#include <string>
#include <unordered_set>

#include <glm/glm.hpp>

#include <glow/Changeable.h>
#include <unordered_map>
#include <map>


class InputMapping;

template<typename T> class PropertyImpl;
template<typename T> class PropertyCollection;
class AbstractPropertyCollection;

/**
 *  Keeps track of properties and loads ini files.
 *  Properties will be updated when a new ini file is loaded.
 *  Implements glow::Changeable, so glow::ChangeListener can
 *  be notified about changes.
 */
class PropertyManager : public glow::Changeable {
public:
    PropertyManager();
    virtual ~PropertyManager();

    void load(const std::string& file, const std::string& prefix = "");

    template<typename T> PropertyImpl<T>* getImpl(const std::string& key);
    template<typename T> PropertyImpl<T>* getImpl(const std::string& key, const T& defaultValue);

    static PropertyManager* instance();
    static void reset();

    template<typename T> T get(const std::string& name);
    template<typename T> T get(const std::string& name, const T& defaultValue);

    bool hasGroup(const std::string& name);


protected:
    template<typename T>
    PropertyCollection<T>* getPropertyCollection();
    template<typename T>
    void addPropertyCollection(PropertyCollection<T>* collection);

    std::unordered_set<std::string> m_groups;
    std::unordered_map<const std::type_info*, std::unique_ptr<AbstractPropertyCollection>> m_propertyCollections;

    static PropertyManager* s_instance;
};

#include "propertymanager.inl"
