#pragma once
#include <map>

class FloatProperty;


class PropertyManager {

public:
    virtual ~PropertyManager();
    
    void load(std::string file);

    void registerFloatProp(FloatProperty * prop);
    void unregisterFloatProp(FloatProperty * prop);

    static PropertyManager * getInstance();

private:
    PropertyManager();
    void updateFloatProps(std::string key, float value);

    std::map<std::string, float> m_floatValues;
    std::multimap<std::string, FloatProperty *> m_floatProps;

    static PropertyManager * s_instance;
};

