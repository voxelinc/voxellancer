#include "propertymanager.h"

#include "def_regex.h"

#include <string>
#include <fstream>
#include <iostream>

#include <glow/logging.h>

#include "propertycollection.h"
#include "input/inputmapping.h"


// some string, some spaces, equals, some spaces, some string, maybe a comment
static regexns::regex line_regex() { return regexns::regex(R"(^([\w\.]*) *= *(.+?)( *#.*)?$)"); }
static regexns::regex title_regex() { return regexns::regex(R"(^\[(\w+)\])"); }

static regexns::regex float_regex() { return regexns::regex(R"(^[-+]?\d*\.?\d*$)"); }
static regexns::regex int_regex() { return regexns::regex(R"(^([-+]?\d+)|(0x([0-9a-fA-F])+)$)"); } // stoi can also parse hex values
static regexns::regex bool_regex() { return regexns::regex(R"(^(true|false)$)"); }
static regexns::regex char_regex() { return regexns::regex(R"(^\w$)"); }
static regexns::regex string_regex() { return regexns::regex(R"(^.*$)"); }
static regexns::regex vec3_regex() { return regexns::regex(R"(^([-+]?\d*\.?\d*), ?([-+]?\d*\.?\d*), ?([-+]?\d*\.?\d*)$)"); }
static regexns::regex input_mapping_regex() { return regexns::regex(R"(^InputMapping\((\d+), ?(\d+), ?([-+]?\d*\.?\d*)\)$)"); }

static glm::vec3 vec3Converter(const std::string &s) {
    regexns::smatch matches;
    regexns::regex_match(s, matches, vec3_regex());

    float x = std::stof(matches[1]);
    float y = std::stof(matches[2]);
    float z = std::stof(matches[3]);

    return glm::vec3(x, y, z);
}

static InputMapping inputMappingConverter(const std::string &s) {
    regexns::smatch matches;
    regexns::regex_match(s, matches, input_mapping_regex());

    InputType type = static_cast<InputType>(std::stoi(matches[1]));
    int index = std::stoi(matches[2]);
    float max_value = std::stof(matches[3]);

    return InputMapping(type,index,max_value);
}

PropertyManager::PropertyManager():
    m_floatProperties(new PropertyCollection<float>(float_regex(), [](std::string s) { return std::stof(s); })),
    m_intProperties(new PropertyCollection<int>(int_regex(), [](std::string s) { return std::stoi(s, 0, 0); })), // base=0 allows adding 0x to parse hex
    m_charProperties(new PropertyCollection<char>(char_regex(), [](std::string s) { return s[0]; })),
    m_boolProperties(new PropertyCollection<bool>(bool_regex(), [](std::string s) { return s == "true" ? true : false; })),
    m_stringProperties(new PropertyCollection<std::string>(string_regex(), [](std::string s) { return s; })),
    m_vec3Properties(new PropertyCollection<glm::vec3>(vec3_regex(), vec3Converter)),
    m_inputMappingProperties(new PropertyCollection<InputMapping>(input_mapping_regex(), inputMappingConverter))
{

}

PropertyManager::~PropertyManager() {
    delete m_floatProperties;
    delete m_intProperties;
    delete m_charProperties;
    delete m_boolProperties;
    delete m_stringProperties;
    delete m_vec3Properties;
}


void PropertyManager::load(std::string file)
{
    std::ifstream input(file);
    std::string line;
    std::string title = "";

    if (!input.is_open()) {
        glow::fatal("PropertyManager: could not open %;", file);
        throw std::runtime_error("Critical configuration file not readable");
    }

    while (std::getline(input, line))
    {
        regexns::smatch matches;

        bool isTitle = regexns::regex_match(line, matches, title_regex());
        if (isTitle) {
            title = matches[1];
            continue;
        }

        bool isLine = regexns::regex_match(line, matches, line_regex());
        if (isLine) {
            std::string key, key_temp, value;
            key_temp = matches[1];
            key = title + '.' + key_temp;
            value = matches[2];
            int success = 0;

            if (m_floatProperties->update(key, value)) success++;
            if (m_intProperties->update(key, value)) success++;
            if (m_boolProperties->update(key, value)) success++;
            if (m_charProperties->update(key, value)) success++;
            if (m_stringProperties->update(key, value)) success++;
            if (m_vec3Properties->update(key, value)) success++;
            if (m_inputMappingProperties->update(key, value)) success++;

            if (success == 0) {
                glow::warning("PropertyManager: no match %;: %; (line: %;)", key, value, line);
            }
        }
    }

    changed();
}

PropertyManager * PropertyManager::instance()
{
    if (s_instance == nullptr) {
        s_instance = new PropertyManager();
    }
    return s_instance;
}


void PropertyManager::reset()
{
    if (s_instance != nullptr) {
        delete s_instance;
        s_instance = nullptr;
    }
}

PropertyManager * PropertyManager::s_instance;

// any better idea or maybe generate these with macros?
template <>
PropertyCollection<int> * PropertyManager::getPropertyCollection(Property<int> * prop)
{
    return m_intProperties;
}

template <>
PropertyCollection<char> * PropertyManager::getPropertyCollection(Property<char> * prop)
{
    return m_charProperties;
}

template <>
PropertyCollection<float> * PropertyManager::getPropertyCollection(Property<float> * prop)
{
    return m_floatProperties;
}

template <>
PropertyCollection<bool> * PropertyManager::getPropertyCollection(Property<bool> * prop)
{
    return m_boolProperties;
}

template <>
PropertyCollection<std::string> * PropertyManager::getPropertyCollection(Property<std::string> * prop)
{
    return m_stringProperties;
}

template <>
PropertyCollection<glm::vec3> * PropertyManager::getPropertyCollection(Property<glm::vec3> * prop)
{
    return m_vec3Properties;
}

template <>
PropertyCollection<InputMapping> * PropertyManager::getPropertyCollection(Property<InputMapping> * prop) {
    return m_inputMappingProperties;
}
