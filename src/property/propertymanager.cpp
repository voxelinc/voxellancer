#include <regex>
#include <fstream>
#include <iostream>

#include "propertymanager.h"


// some string, some spaces, equals, some spaces, some string, maybe a comment
static std::regex line_regex(R"(^([\w\.]*) *= *(.+?)( *#.*)?$)");
static std::regex title_regex(R"(^\[(\w+)\])");

static std::regex float_regex(R"(^\d*\.?\d*$)");
static std::regex int_regex(R"(^\d+$)");
static std::regex bool_regex(R"(^(true|false)$)");
static std::regex char_regex(R"(^\w$)");


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

            if (std::regex_match(value, float_regex)) {
                m_floatProperties.update(key, std::stof(value));
            } 
            if (std::regex_match(value, int_regex)) {
                m_intProperties.update(key, std::stoi(value));
            } 
            if (std::regex_match(value, bool_regex)) {
                bool bValue = value == "true" ? true : false;
                m_boolProperties.update(key, bValue);
            } 
            if (std::regex_match(value, char_regex)) {
                m_charProperties.update(key, value[0]);
            } 
            m_stringProperties.update(key, value);
            
        }
    }
}

PropertyManager * PropertyManager::getInstance()
{
    if (s_instance == nullptr) {
        s_instance = new PropertyManager();
    }
    return s_instance;
}

void PropertyManager::registerProp(Property<float> * prop)
{
    m_floatProperties.registerProp(prop);
}

void PropertyManager::registerProp(Property<int> * prop)
{
    m_intProperties.registerProp(prop);
}

void PropertyManager::registerProp(Property<bool> * prop)
{
    m_boolProperties.registerProp(prop);
}

void PropertyManager::registerProp(Property<char> * prop)
{
    m_charProperties.registerProp(prop);
}

void PropertyManager::registerProp(Property<std::string> * prop)
{
    m_stringProperties.registerProp(prop);
}

void PropertyManager::unregisterProp(Property<float> * prop)
{
    m_floatProperties.unregisterProp(prop);
}

void PropertyManager::unregisterProp(Property<int> * prop)
{
    m_intProperties.unregisterProp(prop);
}

void PropertyManager::unregisterProp(Property<bool> * prop)
{
    m_boolProperties.unregisterProp(prop);
}

void PropertyManager::unregisterProp(Property<char> * prop)
{
    m_charProperties.unregisterProp(prop);
}

void PropertyManager::unregisterProp(Property<std::string> * prop)
{
    m_stringProperties.unregisterProp(prop);
}


PropertyManager::PropertyManager() :
    m_floatProperties(),
    m_intProperties(),
    m_charProperties(),
    m_boolProperties(),
    m_stringProperties()
{
    
}

PropertyManager::~PropertyManager()
{

}

PropertyManager * PropertyManager::s_instance;

