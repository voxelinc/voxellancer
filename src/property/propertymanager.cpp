#include "propertymanager.h"


#include <string>
#include <fstream>
#include <iostream>

#include <glow/logging.h>

#include "propertycollection.h"
#include "propertyconverter.h"
#include "propertyregex.h"

#include "input/inputmapping.h"


PropertyManager::PropertyManager():
    m_floatProperties(new PropertyCollection<float>(float_regex(), [](std::string s) { return std::stof(s); })),
    m_intProperties(new PropertyCollection<int>(int_regex(), [](std::string s) { return std::stoi(s, nullptr, 0); })), // base=0 allows adding 0x to parse hex
    m_uint32Properties(new PropertyCollection<uint32_t>(uint32_regex(), [](std::string s) { return std::stoul(s, nullptr, 0); })), // base=0 allows adding 0x to parse hex
    m_charProperties(new PropertyCollection<char>(char_regex(), [](std::string s) { return s[0]; })),
    m_boolProperties(new PropertyCollection<bool>(bool_regex(), [](std::string s) { return s == "true" ? true : false; })),
    m_stringProperties(new PropertyCollection<std::string>(string_regex(), [](std::string s) { return s; })),
    m_vec2Properties(new PropertyCollection<glm::vec2>(vec2_regex(), PropertyConverter::vec2Converter)),
    m_vec3Properties(new PropertyCollection<glm::vec3>(vec3_regex(), PropertyConverter::vec3Converter)),
    m_vec4Properties(new PropertyCollection<glm::vec4>(vec4_regex(), PropertyConverter::vec4Converter)),
    m_inputMappingProperties(new PropertyCollection<InputMapping>(input_mapping_regex(), PropertyConverter::inputMappingConverter)),
    m_listProperties(new PropertyCollection<std::list<std::string>>(list_regex(), PropertyConverter::listConverter))
{

}

PropertyManager::~PropertyManager() {

}


void PropertyManager::load(const std::string& file, const std::string& prefix) {
    std::ifstream input(file);
    std::string line;
    std::string title = "";

    if (!input.is_open()) {
        glow::fatal("PropertyManager: could not open %;", file);
        throw std::runtime_error("Critical configuration file not readable");
    } else {
        //glow::info("PropertyManager: Loading %; with prefix '%;'", file, prefix);
    }

    std::string keyPrefix = prefix.empty() ? "" : prefix + ".";

    while (std::getline(input, line)) {
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
            key = keyPrefix + title + '.' + key_temp;
            value = matches[2];
            int success = 0;

            if (m_floatProperties->update(key, value)) success++;
            if (m_intProperties->update(key, value)) success++;
            if (m_uint32Properties->update(key, value)) success++;
            if (m_boolProperties->update(key, value)) success++;
            if (m_charProperties->update(key, value)) success++;
            if (m_stringProperties->update(key, value)) success++;
            if (m_vec2Properties->update(key, value)) success++;
            if (m_vec3Properties->update(key, value)) success++;
            if (m_vec4Properties->update(key, value)) success++;
            if (m_inputMappingProperties->update(key, value)) success++;
            if (m_listProperties->update(key, value)) success++;


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

PropertyManager* PropertyManager::s_instance;


// any better idea or maybe generate these with macros?
template <>
PropertyCollection<int>* PropertyManager::getPropertyCollection() {
    return m_intProperties.get();
}

template <>
PropertyCollection<uint32_t>* PropertyManager::getPropertyCollection() {
    return m_uint32Properties.get();
}

template <>
PropertyCollection<char>* PropertyManager::getPropertyCollection() {
    return m_charProperties.get();
}

template <>
PropertyCollection<float>* PropertyManager::getPropertyCollection() {
    return m_floatProperties.get();
}

template <>
PropertyCollection<bool>* PropertyManager::getPropertyCollection() {
    return m_boolProperties.get();
}

template <>
PropertyCollection<std::string>* PropertyManager::getPropertyCollection() {
    return m_stringProperties.get();
}

template <>
PropertyCollection<glm::vec2>* PropertyManager::getPropertyCollection() {
    return m_vec2Properties.get();
}

template <>
PropertyCollection<glm::vec3>* PropertyManager::getPropertyCollection() {
    return m_vec3Properties.get();
}

template <>
PropertyCollection<glm::vec4>* PropertyManager::getPropertyCollection() {
    return m_vec4Properties.get();
}

template <>
PropertyCollection<InputMapping>* PropertyManager::getPropertyCollection() {
    return m_inputMappingProperties.get();
}

template <>
PropertyCollection<std::list<std::string>>* PropertyManager::getPropertyCollection() {
    return m_listProperties.get();
}

