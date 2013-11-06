#include <regex>
#include <string>
#include <fstream>
#include <iostream>

#include <glow/logging.h>

#include "propertymanager.h"


// some string, some spaces, equals, some spaces, some string, maybe a comment
static std::regex line_regex(R"(^([\w\.]*) *= *(.+?)( *#.*)?$)");
static std::regex title_regex(R"(^\[(\w+)\])");

static std::regex float_regex(R"(^\d*\.?\d*$)");
static std::regex int_regex(R"(^\d+$)");
static std::regex bool_regex(R"(^(true|false)$)");
static std::regex char_regex(R"(^\w$)");
static std::regex string_regex(R"(^.*$)");


PropertyManager::PropertyManager() :
m_floatProperties(float_regex, [](std::string s) { return std::stof(s); }),
m_intProperties(int_regex, [](std::string s) { return std::stoi(s); }),
m_charProperties(char_regex, [](std::string s) { return s[0]; }),
m_boolProperties(bool_regex, [](std::string s) { return s == "true" ? true : false; }),
m_stringProperties(string_regex, [](std::string s) { return s; })
{

}

PropertyManager::~PropertyManager()
{
}

void PropertyManager::load(std::string file)
{
    std::ifstream input(file);
    std::string line;
    std::string title = "";

    if (!input.is_open()) {
        glow::warning("PropertyManager: could not open %;", file);
    }

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
            int success = 0;

            if (m_floatProperties.update(key, value)) success++;
            if (m_intProperties.update(key, value)) success++;
            if (m_boolProperties.update(key, value)) success++;
            if (m_charProperties.update(key, value)) success++;
            if (m_stringProperties.update(key, value)) success++;

            if (success == 0) {
                glow::warning("PropertyManager: no match %;: %; (line: %;)", key, value, line);
            }
        }
    }

    changed();
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

void PropertyManager::clear()
{
    if (s_instance != nullptr) {
        delete s_instance;
        s_instance = nullptr;
    }
}

PropertyManager * PropertyManager::s_instance;

