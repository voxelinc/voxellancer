#include <regex>
#include <fstream>

#include "propertymanager.h"
#include "floatproperty.h"
#include <iostream>


// some string, some spaces, equals, some spaces, some string
static std::regex line_regex(R"(^([\w\.]*) *= *(".*?"|[\w\.]*))");
static std::regex title_regex(R"(^\[(\w+)\])");

static std::regex float_regex(R"(^\d*\.?\d*$)");
static std::regex int_regex(R"(^\d+$)");

void PropertyManager::load(std::string file)
{
    std::ifstream input(file);
    std::string line;
    std::string title = "";

    while (std::getline(input, line))
    {
        std::smatch matches;

        std::regex_match(line, matches, title_regex);
        if (matches.size() > 0) {
            title = matches[1];
            continue;
        }        
        std::regex_match(line, matches, line_regex);
        if (matches.size() > 0) {
            std::string key, key_temp, value;
            key_temp = matches[1];
            key = title + '.' + key_temp;
            value = matches[2];

            //m_stringValues[key] = value;
            if (std::regex_match(value, float_regex)) {
                float fValue = std::stof(value);
                m_floatValues[key] = fValue;
                updateFloatProps(key, fValue);
            }
            if (std::regex_match(value, int_regex)) {
                //m_intValues[key] = std::stoi(value);
            }
        }
    }
}

void PropertyManager::updateFloatProps(std::string key, float value)
{
    auto result = m_floatProps.equal_range(key);
    for (auto iter = result.first; iter != result.second; ++iter)
    {
        FloatProperty * prop = (*iter).second;
        prop->set(value);
    }
}

PropertyManager * PropertyManager::getInstance()
{
    if (s_instance == nullptr) {
        s_instance = new PropertyManager();
    }
    return s_instance;
}

void PropertyManager::registerFloatProp(FloatProperty * prop)
{
    m_floatProps.insert(std::pair<std::string, FloatProperty *>(prop->name(), prop));
    auto iter = m_floatValues.find(prop->name());
    if (iter != m_floatValues.end()) {
        prop->set(iter->second);
    }
}

void PropertyManager::unregisterFloatProp(FloatProperty * prop)
{
    auto iter = m_floatProps.find(prop->name());
    for (; iter != m_floatProps.end(); ++iter) {
        if (iter->second == prop) {
            m_floatProps.erase(iter);
            break;
        }
    }
}

PropertyManager::PropertyManager() :
    m_floatProps(),
    m_floatValues()
{
    
}

PropertyManager::~PropertyManager()
{

}

PropertyManager * PropertyManager::s_instance;

